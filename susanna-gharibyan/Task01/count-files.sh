#!/bin/bash

function Count() {
    files_list=$(find $1 -type f)
    count=$(echo "$files_list" | wc -l)

    echo "$1: $count"
}

if [ $# != 1 ]; then
    echo "argument should be passed"
    exit 1
fi

Count $1

