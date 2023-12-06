#!/bin/bash


if [[ $# != 1 ]]
then
	echo "invalid argument";
	exit 1;
	
fi

ans=0

while read -r num
do
    ((ans+=num))
    if [[ $1 -le $ans ]]
    then
        echo $ans
        exit 1
    fi
done

echo $ans
