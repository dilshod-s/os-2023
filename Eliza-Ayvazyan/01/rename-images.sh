#!/bin/bash 

function rename(){
  for file in *.jpg; do
    if [[ -f "$file" ]]; 
    then
      if [[ -z "$(echo "$file" | grep -o '^[0-9]\{4\}-[0-9]\{2\}-[0-9]\{2\}')" ]];
      then
        date=$(stat -c %y "$file" | awk -F ' ' '{print $1}')
        new_name="${date}-${file}"
        mv "$file" "$new_name"
      fi
    fi
  done
}

rename
