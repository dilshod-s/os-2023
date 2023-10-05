#!/bin/bash

for file in *.jpg
do
    # Get creation info
    date_created=$(stat -c %w $file)
    
    # Get creation date from info
    date_created=$(echo $date_created | cut -d' ' -f1)

    # Rename the image
    new_name="${date_created}-${file}"
    mv $file $new_name

    echo "renamed $file to $new_name"
done

