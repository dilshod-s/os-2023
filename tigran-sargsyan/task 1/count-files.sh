#!/bin/bash

count_files() {
    local dir=$1 
    local count=$(ls -1 "$dir" | wc -l) 
    echo "$count" 
}

count_files "$1" 
