#!/bin/bash


if [[ $# != 1 ]]
then
	exit 1
fi

sum=0

read my_limit
for (( sum=0; $sum < my_limit; ))

do
read num
let sum+=num
done

echo $sum