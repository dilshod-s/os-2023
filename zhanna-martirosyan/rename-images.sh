#!/bin/bash

for image in *.jpg
do
    if [ -f "$image" ] 
	then
	if [[ "$image" =~ [0-9]{4}-[0-9]{2}-[0-9]{2}-.*\.jpg ]]
	then
		echo "$image"
        else
        	date=$(date -r "$image" "+%Y-%m-%d")
        	new="$date-$image"
        	mv "$image" "$new"
        	echo "New name for $image is $new"
	fi
    fi
done

exit 0

