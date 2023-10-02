#!/bin/bash

__count_files_in_directory() {
  if [ -d "$1" ]; then
    ( cd $1 && ls -1 | wc -l )
  fi
}

file_count=$(__count_files_in_directory "$1")

echo "$file_count"
