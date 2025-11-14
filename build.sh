#!/bin/bash
set -e

BUILD_DIR="build"

# Create build directory if it doesn't exist
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Run CMake and build all targets
cmake -DCMAKE_C_COMPILER=gcc-14 -DCMAKE_CXX_COMPILER=g++-14 ..
cmake --build . --target all
