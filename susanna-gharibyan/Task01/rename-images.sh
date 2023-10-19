#!/bin/bash

for img in $(ls *.jpg)
do
    if [[ $img =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}-.*\.jpg$ ]]
    then
        echo "$img is renamed already"
    else
        creation_date=$(stat -c %w $img | cut -d' ' -f1)
        new_name="${creation_date}-${img}"
        mv $img $new_name
    fi
done
