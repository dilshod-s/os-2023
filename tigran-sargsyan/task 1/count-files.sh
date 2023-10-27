#!/bin/bash

count_files() {
    local dir=$1 
    local count=$(ls -1 "$dir" | wc -l) //подсчет строк в dir
    echo "$count" //like_return
}

count_files "$1" //call_function
