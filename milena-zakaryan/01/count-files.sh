#!/bin/bash 
 
file_count() { 
  directory="$1" 
  if [[ -d "$directory" ]]
  then 
    file_count=$(find $directory -type f | wc -l) 
    echo " $directory: $file_count" 
  else 
    echo "invalid directory" 
  fi 
} 
 
if [[ $# == 1 ]]
then 
  file_count $1
else 
  echo "argument should be passed" 
fi