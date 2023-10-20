#!/bin/bash

read limit

sum=0

while  read -r num 
do
 if [[ $sum -ge $limit ]]
    then
        break
    fi
    let sum+=num
done

echo $sum
