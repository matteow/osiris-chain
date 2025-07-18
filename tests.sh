#!/bin/bash
set -e

# Przechodzi do katalogu build i uruchamia testy
cd build
ctest --output-on-failure
