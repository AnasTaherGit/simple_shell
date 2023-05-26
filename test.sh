#!/bin/bash
# author: @winsid

# ANSI color codes
GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"  # No color

# Compile hsh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -g -o hsh

# Set test folder
test_folder="tests_cd"

# Get list of files in tests directory
files=$(ls "$test_folder")

# Remove old result files
for file in "$test_folder"/*; do
    if [[ $file == *.result ]]; then
        rm "$file"
    fi
done

# Create test_ok folder inside test_folder
mkdir -p "$test_folder/test_ok"

# Move all non result files from test_ok to test_folder
for file in "$test_folder"/test_ok/*; do
    if [[ $file != *.result ]]; then
        mv "$file" "$test_folder"
    fi
done

# update file list

files=$(ls "$test_folder")

# chmod checker.bash
chmod u+x "$test_folder/checker.bash"

# Run tests and save output to files, suppress result in terminal
for file in $files; do
    if [[ $file != "checker.bash" ]] && [[ $file != *.result ]] && [[ $file != "test_ok" ]]; then
        echo "Running test $file"
        output=$("$test_folder/checker.bash" ./hsh "$test_folder/$file" 2>&1)
        echo "$output" > "$test_folder/$file.result"
        if [[ $output == "OK" ]]; then
            echo -e "${GREEN}$output${NC}"
            # move result files to test_ok directory
            mv "$test_folder/$file.result" "$test_folder/test_ok/$file.result"
        else
            echo -e "${RED}NOT OK${NC}"
        fi
    fi
done
