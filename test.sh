#!/bin/bash

# Compile hsh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -g -o hsh

# Get list of files in tests directory
files=$(ls tests)

# Remove old result files
for file in $files; do
    if [[ $file == *.result ]]; then
        rm "tests/$file"
    fi
done

# Run tests and save output to files, suppress result in terminal
for file in $files; do
    if [[ $file != "checker.bash" ]] && [[ $file != *.result ]]; then
        echo "Running test $file"
        tests/checker.bash ./hsh "tests/$file" > "tests/$file.result" 2>&1
    fi
done
