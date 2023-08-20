#!/bin/bash

# Compile the C++ program
g++ -std=c++11 main.cpp -o my_program

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # echo "Compilation successful."

    # Run the C++ program with specified arguments
    # ./my_program "$1" "$2" "$3"
else
    echo "Compilation failed."
fi
