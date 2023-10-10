#!/bin/bash

for file in *.jpg;do
    if [ -f "$file" ]; then
        if [[ "$file" =~ [0-9]{4}-[0-9]{2}-[0-9]{2}-.*\.jpg ]]; then
	  echo "$file already renamed"
        else
            data=$(stat -c %y "$file" | cut -d ' ' -f 1)
            new="${data}-${file}"
            mv "$file" "$new"
            echo "$file -> $new"
        fi
    fi
done
exit 0
