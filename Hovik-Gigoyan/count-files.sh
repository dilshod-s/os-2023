#!/bin/bash

foo()
{
        local dir="$1"
	local count=$(find "$dir" -maxdepth 1 -type f | wc -l)
	echo "$count"
}

if [ $# -ne 1 ]; then
	echo "$0"
	exit 1
fi

dir="$1"
foo "$dir"
