#!/bin/bash

for jpg_file in *.jpg; do
  if [ -f "$jpg_file" ]; then
    creation_date=$(stat -c %y "$jpg_file" | cut -d ' ' -f 1)
    new_name="${creation_date}-${jpg_file}"
    if [ ! -e "$new_name" ]; then
      mv "$jpg_file" "$new_name"
      echo "File renamed: $jpg_file -> $new_name"
    fi
  fi
done

