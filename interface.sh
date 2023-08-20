
#!/bin/bash

# Check if the required number of arguments are provided
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <C> <input_file> <output_file>"
    exit 1
fi

# Check if the compiled program exists
if [ ! -f "my_program" ]; then
    echo "The compiled program 'my_program' does not exist. Run compile.sh first."
    exit 1
fi

# Run the compiled C++ program with specified arguments
./my_program "$1" "$2" "$3"