#!/bin/bash

gcd(){
    M=$1
    N=$2
    if [[ $M -eq $N ]]
    then
        echo "GCD is $M"
    elif [[ $M -gt $N ]]
    then
        gcd $(($M-$N)) $N
    else
        gcd $(($N-$M)) $M
    fi
}

while true
do
    read firstarg
    if [[ -z $firstarg ]]
    then
        echo "bye"
        break
    fi
    read secondarg
    if [[ -z $secondarg ]]
    then
        echo "bye"
        break
    else
        gcd $firstarg $secondarg
    fi
done
