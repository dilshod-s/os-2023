#!/bin/bash

for file in *.jpg; 
do
  if [ -f "$file" ]; 
  then
    
    data=$(stat -c "%y" "$file" | cut -d ' ' -f1)

    delete_hyphen=$(echo "$data" | tr -d '-')

    new_jpg="${delete_hyphen}-${file}"

    if [ ! -e "$new_jpg" ]; 
    then
      mv "$file" "$new_jpg"
      echo "new name: $file -> $new_jpg"
      
    else
      echo " already exist $new_jpg"
    fi
  fi
done

