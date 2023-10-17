#!/bin/bash

sum=0

if [[ $# != 1 ]]
then
	echo "argument should be passed";
	exit 1;
fi

while [[ $sum < $1 ]]
do
	read num;
     if [[ $? != 0 ]]
	then
	  exit 0
     fi
	let sum+=num;
	echo "Current sum: $sum";
done

