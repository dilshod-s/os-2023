#!/bin/bash

function count_files(){
cd $1 | ls -1 | wc -l
}

sum=$(count_files $1)
echo $sum
