#!/bin/bash


if [[ $# != 1 ]]
then
	echo "invalid argument";
	exit 1;
	
fi

ans=0

while [[ $ans < $1 ]]
do
	read num;	
	((ans+=num))
done

echo $ans