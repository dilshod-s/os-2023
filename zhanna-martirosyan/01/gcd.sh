#!/bin/bash

function gcd(){
	if [[ $2 -eq 0 ]]
	then
		echo "GCD is $1"
	else
		gcd "$2" "$(($1 % $2))"
fi
}

read var1
read var2

if [[ -z "$var1" || -z "$var2" ]]
	then
		echo "bye"
        	break
    	fi

echo "$(gcd $var1 $var2)"	

exit 0
