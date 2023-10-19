#!/bin/bash

function f_count(){
    
if [[ -d "$1" ]]

    then
    cd $1 | ls -1 | wc -l
fi
}

sum=$(f_count $1)

echo $sum
