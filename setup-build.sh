#!/bin/sh

cd $(dirname $0)
set -e

rm -rf build
mkdir build
meson.py build
ninja -C build test
