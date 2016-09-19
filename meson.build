project('flatcc-issue4', 'c')

# schema paths should be absolute for rules to work properly.
schema_dir = meson.current_source_dir() 

# Path to the schema from flatcc issue #4.
issue4_fbs = schema_dir + '/schema/union_with_empty.fbs'

# `subprojects/flatcc.wrap` imports flatcc via git.
flatcc = subproject('flatcc')

# Rule that generates arbitrary flatbuffers schema to C headers.
flatcc_gen = flatcc.get_variable('flatcc_gen')

# Runtime library for building flatbuffers (shared or static based on
# default_library option which defaults to shared.
libflatccrt = flatcc.get_variable('libflatccrt')

# Choose specific library type, static or shared:
# libflatccrt = flatcc_sp.get_variable('libflatccrt_sta')
# libflatccrt = flatcc_sp.get_variable('libflatccrt_sha')

# Include path to `flatcc/include`.
flatcc_include = flatcc.get_variable('flatcc_include')

# Common headers are generated in a separate step to allow for
# concurrent builds.
flatcc_common = flatcc.get_variable('flatcc_common')

# This compiles our flatbuffers schema into C headers
issue4_schema = flatcc_gen.process(issue4_fbs)

# This is a user provided test case for issue #4.
issue4 = executable('flatcc-issue4', 'src/issue4.c',
    issue4_schema,
    flatcc_common,
    link_with: libflatccrt,
    include_directories: flatcc_include)

test('issue4', issue4)
