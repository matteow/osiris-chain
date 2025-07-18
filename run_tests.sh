#!/bin/bash
set -e

cd /osiris-core
mkdir -p build
cd build

cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . -- -j$(nproc)
ctest --output-on-failure
