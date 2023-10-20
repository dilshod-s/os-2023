#!/bin/bash

for file in *.jpg
do
    if [[ $file =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}-.*\.jpg$ || $file =~ ^[0-9]{4}-[0-9]{1}-[0-9]{2}-.*\.jpg$ || $file =~ ^[0-9]{4}-[0-9]{2}-[0-9]{1}-.*\.jpg$ || $file =~ ^[0-9]{4}-[0-9]{1}-[0-9]{1}-.*\.jpg$ ]]
    then
        echo "$file already renamed. Skiping..."
    else
        # Get creation info
        date_created=$(stat -c %w $file)
    
        # Get creation date from info
        date_created=$(echo $date_created | cut -d' ' -f1)

        # Rename the image
        new_name="${date_created}-${file}"
        mv $file $new_name

        echo "Renamed $file to $new_name"
    fi
done

