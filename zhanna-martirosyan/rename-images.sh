#!/bin/bash

for image in *.jpg
do
    if [ -f "$image" ] 
	then
        	date=$(date -r "$image" "+%Y-%m-%d")
        	new="$date-$image"
        	mv "$image" "$new"
        	echo "New name for $image is $new"
    fi
done

exit 0
