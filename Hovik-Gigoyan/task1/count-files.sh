#!/bin/bash

count_files() {
    local directory=$1
    if [ ! -d "$directory" ]; then
        echo "Директория не найдена: $directory"
        return 1
    fi

    local count=0
    for file in "$directory"/*; do
        if [ -f "$file" ]; then
            count=$((count + 1))
        fi
    done
    echo $count
}

if [ "$#" -ne 1 ]; then
    echo "Использование: $0 <директория>"
    exit 1
fi

count_files "$1"
