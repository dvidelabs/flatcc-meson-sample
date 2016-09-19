The purpose of this project is to demonstrate how to include flatcc as
dependency of a small C program that builds flatbuffers. This works by
using the Meson build system which is a more userfriendly CMake/Ninja
style build system with a sort of built-in package management.

This project depends on the `meson` branch of flatcc which is currently
experimental.

We use a the user provided test case for
[flatcc issue 4](https://github.com/dvidelabs/flatcc/issues/4) as an
example.

To get started, please inspect the `subprojects/flatcc.wrap` file to
ensure the git url and revision is up to date.

Dependencies: C compiler tool chain, git, ninja-build,
python3, and [meson 0.34.0+](https://github.com/mesonbuild/meson).

Note: By design Meson only depends on core python3 libraries and can be
run from source checked out via github.

To fetch, build and run test:

    step 1: mkdir build
    step 2: meson build (or meson.py build)
    step 3: ninja -C build test
    step 4: there is no step 4

or you can call `setup-build.sh` which does the same.

Yes, now you can have automagically built schema headers with solid build
dependencies with very little setup.

To test dependencies, try

    ninja -C build
    # <nothing to build>
    thouch schema/*.fbs
    ninja -C build
    # linking app

Note that this also works with schema files that include other schema
files as is the case in the main flatcc `monster_test` project, but here
we have a lighter setup. The only problem is `ninja -C build clean`
might complain a bit because of unknown output products, But these are
always created via solid dependencies unless the build is manipulated
directly.

Note that Meson can choose a system installed version of flatcc over
fetching a subproject with git. However, because we some nice complation
rules in the subproject, and because it is really fast to fetch and
compile, it is much better to embed flatcc as subproject always.
Just make sure to link executable static. Note: linking statically
typically results in binaries much smaller that the static library
or the shared library size alone, like a factor 10.

If working with many flatbuffers projecst, it is also possible to
download the flatcc repo once and symbolically link it into
subjprojects to avoid repeated downloading.

Also notice the .gitignore file: we ignore our build directory and
everything in the subproject dir except for the .wrap file that fetch
the flatcc repository. The repository is placed in subprojects by git,
but is ignored by our parent git repo. The flatcc project is built in
the build dir and does not touch subprojects after being fetched.

Build times on 4 core i7, 2,2GHz, Ninja/Clang/MacOS
(after fetching flatcc source into subprojects and cleaning build dir)

To set up a new project after cloning this repo, but without having
fetched flatcc yet:

time ./setup-build.sh
        4.10 real         5.53 user         1.29 sys

The above primarily measures the time it takes to clone the flatcc repo
via meson.

Build times broken down after initial clone of flatcc.

    $ rm -rf build/*

    $ time meson build
            0.23 real         0.16 user         0.06 sys

    $ time ninja -C build test
            1.29 real         5.15 user         1.10 sys

    # (again)
    $ time ninja -C build test
            0.17 real         0.13 user         0.03 sys

    # (again without test)
    $ time ninja -C build
    ninja: Entering directory `build'
    ninja: no work to do.
            0.00 real         0.00 user         0.00 sys

    $ touch schema/*.fbs
    $ time ninja -C build
    ninja: Entering directory `build'
    [3/3] Linking target flatcc-issue4
            0.11 real         0.08 user         0.02 sys


