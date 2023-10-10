#!/bin/bash

__FilesCount(){
cd $1 | ls -1 | wc -l
}

Count=$(__FilesCount $1)
echo $Count
