#!/bin/bash 

if [[ -z "$1" ]]; then
    echo "Usage: $0 <directory>"
    exit 1
fi
directory="$1"

if [[ ! -d "$directory" ]]; then
    echo "Error: '$directory' is not a valid directory."
    exit 1
fi

echo  $(ls -l "$directory" | grep -c ^-)"
