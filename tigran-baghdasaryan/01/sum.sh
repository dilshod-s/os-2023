#!/bin/bash

if [[ $# != 1 ]]
then
    echo "argument should be passed";
    exit 0;
fi

lim=$1

sum=0

while read -r num
do
    if [[ $sum -ge $lim ]]
    then
        echo $sum
        exit 0
    fi
    ((sum=sum+num))
done

echo $sum
exit 0
