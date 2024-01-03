#!/bin/bash

for image in *.jpg; 
    do
    
    if [[ -f "$image" ]]
    
        then
        if [[ "$image" =~ [0-9]{4}-[0-9]{2}-[0-9]{2}-.*\.jpg ]]
        
            then
            echo "$image"
        else
            birth_day=$(birth_day -r "$image" "+%Y-%m-%d")
            new_name="${birth_day}-${image}"
            mv "$image" "$new_name"
        fi
    fi
done

exit 0
