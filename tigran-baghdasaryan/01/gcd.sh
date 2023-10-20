#!/bin/bash

while true
do
    echo "Enter the first number (or press Enter to exit): "
    read m
    if [[ -z $m ]]
    then
        echo "Exiting..."
        exit 0
    fi
    
    echo "Enter the second number (or press Enter to exit): "
    read n
    if [[ -z $n ]]
    then
        echo "Exiting..."
        exit 0
    fi
    
    
    #gcd logic
    while [[ $m != $n ]]
    do
        if [[ $m -ge $n ]]
        then
            m=$((m - n))
        else
            n=$((n - m))
        fi
    done
    
    
    result=$m
    
    echo "GCD: $result"
done

