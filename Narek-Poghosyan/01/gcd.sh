#!/bin/bash

gcd(){
	if [[ $2 -eq 0 ]]
	then
		echo "$1"
	else
		gcd "$2" "$(($1 % $2))"
	fi
		
}

read tiv1
read tiv2

if [[ -z $tiv1 || -z $tiv2 ]]
then	
	echo "bye"
	exit 0
fi

echo "$(gcd $tiv1 $tiv2)"
