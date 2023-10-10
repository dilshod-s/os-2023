#!/bin/bash

for image in *.jpg
do
    if [ -f "$image" ]; then
        date=$(stat -c %y "$image" | cut -d ' ' -f 1)

        new="${date}-${image}"
        mv "$image" "$new"

        echo "New name for $image is $new"
    fi
done

exit 0