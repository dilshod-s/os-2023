#!/bin/bash

for jpg_file in *.jpg; do
  if [ -f "$jpg_file" ]; then
    # Extract the date from the filename if it exists
    creation_date=$(echo "$jpg_file" | grep -oE '[0-9]{4}-[0-9]{2}-[0-9]{2}')

    if [ -z "$creation_date" ]; then
      creation_date=$(stat -c %y "$jpg_file" | cut -d ' ' -f 1)
      new_name="${creation_date}-${jpg_file}"
      
      if [ ! -e "$new_name" ]; then
        mv "$jpg_file" "$new_name"
        echo "File renamed: $jpg_file -> $new_name"
      fi
    fi
  fi
done
