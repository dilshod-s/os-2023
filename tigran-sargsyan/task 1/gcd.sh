#!/bin/bash

gcd() {
    local m=$1
    local n=$2

    if [ $m -eq $n ]; 
    then
        echo "GCD is $m"
    elif [ $m -gt $n ]; 
    then
        gcd $(($m-$n)) $n
    else
        gcd $m $(($n-$m))
    fi
}

while true; 
do
    read -p "Enter two natural numbers (or empty string to exit): " num1 num2
    if [ -z "$num1" ] || [ -z "$num2" ]; 
    then
        echo "bye"
        exit 0
    fi
    gcd $num1 $num2
done
