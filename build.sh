#!/bin/bash
set -e

# Handle clean argument
if [ "$1" == "clean" ]; then
    rm -rf build
    exit 0
fi

# Configure project
echo "Configuring project..."
cmake -B build -DCMAKE_BUILD_TYPE=Debug

# Compile project
echo "Compiling..."
cmake --build build

echo "Success! Executable at: build/OpenGLRenderer"