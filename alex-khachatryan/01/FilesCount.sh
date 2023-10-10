#!/bin/bash

function FilesCount(){

    if [ -d "$1" ]; then
	( cd "$1" && ls -1 | wc -l )
    fi


}

count=$(FilesCount "$1")
echo "$count"
