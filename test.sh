#!/bin/bash
# author: @winsid

# ANSI color codes
GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"  # No color

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
        output=$(tests/checker.bash --diff ./hsh "tests/$file" 2>&1)
        echo "$output" > "tests/$file.result"
        if [[ $output == "OK" ]]; then
            echo -e "${GREEN}$output${NC}"
            # move test and result files to ok_results directory
            mkdir -p ok_results
            mv "tests/$file" "ok_results/$file"
            mv "tests/$file.result" "ok_results/$file.result"
        else
            echo -e "${RED}NOT OK${NC}"
        fi
    fi
done
