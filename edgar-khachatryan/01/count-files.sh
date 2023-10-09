#!/bin/bash

count_files() {
    dir=$1
    file_count=$(find $dir -type f | wc -l)
    if [[ $? != 0 ]];
    then
        exit 1;
    fi
    
    echo $file_count
    exit 0
}

if [[ $# != 1 ]]
then
    echo "argument should be passed";
    exit 1;
fi

directory=$1

file_count=$(count_files $directory)

if [[ $? != 0 ]];
then
    exit 1;
fi

echo "number of files in $directory: $file_count"
exit 0
