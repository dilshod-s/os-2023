#!/bin/bash

file_count() {
  directory="$1"
  if [[ -d "$directory" ]]; then
    file_count=$(find "$directory" -type f | wc -l)
    echo "$directory: $file_count file(s)"
  else
    echo "Error: '$directory' is not a valid directory."
  fi
}

if [[ $# -eq 1 ]]; then
  file_count "$1"
else
  echo "Error: Please provide a directory as an argument."
fi
