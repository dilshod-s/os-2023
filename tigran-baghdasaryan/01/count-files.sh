#!/bin/bash

count_of_files() {
    dir=$1
    file_count=$(find $dir -type f | wc -l)
    if [[ $? != 0 ]];
    then
        exit 0;
    fi
    
    echo $file_count
    exit 0
}


if [[ $# != 1 ]]
then
    echo "argument should be passed";
    exit 0;
fi

directory=$1

file_count=$(count_of_files $directory)

if [[ $? != 0 ]];
then
    exit 0;
fi

echo "Files in $directory: $file_count"
exit 0
