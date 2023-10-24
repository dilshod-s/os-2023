#!/bin/bash 

function rename(){
  for file in *.jpg; do
    if [[ -f "$file" ]]; 
    then
      date=$(stat -c %y "$file" | awk -F ' ' '{print $1}')
      new_name="${date}-${file}"
      mv "$file" "$new_name"
    fi
  done
}

rename
