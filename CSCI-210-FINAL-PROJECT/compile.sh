#!/bin/bash

# Set output file name
output="program.out"

# Find all C++ (.cpp) and C (.c) files
cpp_files=$(find . -name "*.cpp")
c_files=$(find . -name "*.c")

# Compile C++ files with g++
cpp_objects=""
for file in $cpp_files; do
    obj_file="${file%.cpp}.o"
    g++ -c "$file" -o "$obj_file"
    cpp_objects="$cpp_objects $obj_file"
done

# Compile C files with gcc
c_objects=""
for file in $c_files; do
    obj_file="${file%.c}.o"
    gcc -c "$file" -o "$obj_file"
    c_objects="$c_objects $obj_file"
done

# Link all object files together
g++ $cpp_objects $c_objects -o "$output"

# Notify user
echo "Compilation finished. Output: $output"
