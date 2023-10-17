#!/bin/bash

sum=0

if [[ $# != 1 || "$1" =~ ^[0-9]+$ ]]
then
    exit 1
fi

while [[ $sum < $1 ]]
do
	read var
	if [[ -z "$var" ]]
	then
        	break
    	fi
	let sum+=var
done 

echo "$sum"

exit 0
