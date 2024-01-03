#!/bin/bash

sum=0
limit=$1

while read -r number
do
    sum=$((sum + number))
    if [ $sum -gt $limit ]; then
        echo $sum
        exit 0
    fi
done

echo $sum
exit 0
