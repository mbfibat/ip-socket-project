#!/bin/bash

# Create build directory
mkdir build

# Generate build files using CMake
cmake -S . -B build

# Build the project and copy the executable to the bin directory
cmake --build build --target client -j$(grep -c ^processor /proc/cpuinfo)
