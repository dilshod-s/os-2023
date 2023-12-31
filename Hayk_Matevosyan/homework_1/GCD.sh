#!/bin/bash

gcdcode() {
    M=$1
    N=$2
    if [[ $M -eq $N ]]; then
        echo "GCD is $M"
    elif [[ $M -gt $N ]]; then
        diff=$((M - N))
        gcdcode $diff $N
    else
        diff=$((N - M))
        gcdcode $M $diff
    fi
}

while true; do
    read -p "Enter the first number (or 'bye' to exit): " M
    if [[ -z $M || $M == "bye" ]]; then
        echo "Goodbye!"
        break
    fi

    read -p "Enter the second number (or 'bye' to exit): " N
    if [[ -z $N || $N == "bye" ]]; then
        echo "Goodbye!"
        break
    fi

    if [[ ! $M =~ ^[0-9]+$ || ! $N =~ ^[0-9]+$ ]]; then
        echo "Error: Please enter valid numbers."
    else
        gcdcode $M $N
    fi
done
