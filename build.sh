#!/bin/bash
set -e

# Tworzy katalog build i przechodzi do niego
mkdir -p build
cd build

# Generuje pliki makefile poprzez CMake i kompiluje projekt
cmake ..
make -j$(nproc)
