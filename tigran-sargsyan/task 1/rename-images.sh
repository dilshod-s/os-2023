#!/bin/bash

for file in *.jpg; 
do
    if [ -f "$file" ]; 
    then
        date=$(stat -c %y "$file" | cut -d ' ' -f 1)
        mv "$file" "${date}-${file}"
    fi
done
