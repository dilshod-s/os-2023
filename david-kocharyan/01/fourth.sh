#!/bin/bash

for file in *.jpg
do
    if [[ $file =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}-.*\.jpg$ || $file =~ ^[0-9]{4}-[0-9]{1}-[0-9]{2}-.*\.jpg$ || $file =~ ^[0-9]{4}-[0-9]{2}-[0-9]{1}-.*\.jpg$ || $file =~ ^[0-9]{4}-[0-9]{1}-[0-9]{1}-.*\.jpg$ ]]
    then
        echo "$file renamed."
    else
        
        date=$(stat -c %w $file | cut -d ' ' -f1)
    
        
        new_name="${date}-${file}"
        mv $file $new_name

        echo "renamed $file to $new_name"
    fi
done

