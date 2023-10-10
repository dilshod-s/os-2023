#!/bin/bash

for nkar in *.jpg
do
    if [ -f "$nkar" ]; then
        # Check if the filename already contains a date in "YYYY-MM-DD" format
        if [[ "$nkar" =~ [0-9]{4}-[0-9]{2}-[0-9]{2}-.*\.jpg ]]; then
            echo "Skipping $nkar (already renamed)"
        else
            # Get the last modification date using the stat command
            data=$(stat -c %y "$nkar" | cut -d ' ' -f 1)
            new="${data}-${nkar}"
            mv "$nkar" "$new"
            echo "$nkar -> $new"
        fi
    fi
done

exit 0

