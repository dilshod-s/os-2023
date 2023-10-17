#!/bin/bash

gcdcode() {    
    M=$1 
    N=$2  
    if [[ $M -eq $N ]]
    then     
        echo "gcd is $M" 
    elif [[ $M -gt $N ]] 
    then      
        diff=$((M - N)) 
        gcdcode $diff $N
    else 
        diff=$((N - M))     
        gcdcode $M $diff 
    fi
}

while true
do  
read M
if [[ -z $M ]]
then
    echo "bye"
    break
else
    read N
    if [[ -z $M ]]
    then
        echo "bye"
        break
    else
        gcdcode $M $N
    fi 
fi
done
