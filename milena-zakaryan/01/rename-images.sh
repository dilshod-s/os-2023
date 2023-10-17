#!/bin/bash

for file in *.jpg
do 
    if [[ -f "$file" ]]
    then
        if [[ $file =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}-.*\.jpg$ ]]
        then
             echo "$file is renamed"
        else
	    creation_date=$(stat -c %y "$file" | cut -d ' ' -f1)
	    mv "$file" "$creation_date-$file"
            echo "$file -> $creation_date-$file" 
        fi
    fi
done
