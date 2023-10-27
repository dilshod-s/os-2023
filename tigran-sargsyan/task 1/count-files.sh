#!/bin/bash

count_files() {
    local dir=$1 
    local count=$(ls -1 "$dir" | wc -l) local //подсчет строк в dir
    echo "$count" //like return
}

count_files "$1" //call function
