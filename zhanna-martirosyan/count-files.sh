#!/bin/bash

function count() {
	if [ -d "$1" ]; 
	then
		( cd "$1" && ls -1 | wc -l )
	fi
}

result=$(count "$1")

echo "Count of files in "$1": "$result""

exit 0