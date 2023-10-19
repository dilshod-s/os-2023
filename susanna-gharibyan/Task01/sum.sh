#!/bin/bash

sum=0

if [[ $# != 1 ]]
then 
    echo "argument should be passed";
    exit 1;
fi

while read -r num
do
    let sum=sum+num
    
    if [[ $1 -le $sum ]]
    then
        echo $sum
        exit 1
    fi
done

echo $sum
exit 0
