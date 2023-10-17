#!/bin/bash

for image in *.jpg;

  do
  
    if [[ -f "$image" ]] 
        then
        birth_day=$(stat -c %y "$image" | cut -d ' ' -f 1)
        new_name="${birth_day}-${image}"
        
    if [[ ! -e "$new_name" ]] 
        then
        mv "$image" "$new_name"
    fi
    
  fi
  
done
