#!/bin/sh

cd $(dirname $0)
set -e
MESON=$(./get-meson.sh)
rm -rf build
mkdir build
$MESON build
ninja -C build test
