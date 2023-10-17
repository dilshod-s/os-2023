#!/bin/bash

read limit
sum=0
while  read -r num 
do
 if [[ $sum > $limit ]]
    then
        exit
    fi
    let sum+=num
done
echo $sum
