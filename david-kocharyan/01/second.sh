#!/bin/bash

fileCounter() {
  local count=0
  if [ -d "$1" ]; 
  then
    count=$(find "$1" -type f | wc -l)
  else
    echo "Directory not exist"
    exit 1
  fi
  echo "$count"
}

directory="$1"
result=$(fileCounter "$directory")
echo "Count of files in $directory is : $result"

