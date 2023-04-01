#!/bin/bash

# Generate build files using CMake
cmake -S . -B build

# Build the project and copy the executable to the bin directory
cmake --build build -j$(grep -c ^processor /proc/cpuinfo)
