#!/bin/bash

for file in *.jpg; do
    creation_date=$(stat -c %w "$file" | cut -d ' ' -f 1)
    if [ "$creation_date" = '-' ]; then
        creation_date=$(stat -c %y "$file" | cut -d ' ' -f 1)
    fi

    new_filename="${creation_date}-${file}"

    mv "$file" "$new_filename"
done
