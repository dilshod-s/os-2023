#!/bin/bash

__gcd() 
{
    local m="$1"
    local n="$2"

    if [ "$n" -eq 0 ]; then
        echo "GCD is $m"
    else
        __gcd "$n" "$((m % n))"
    fi
}

while true; do
    echo "Input two numbers: "
    read -p "First number -> " num1

    if [ -z "$num1" ]; then
        echo "bye"
        exit 0
    fi
    read -p "Second number -> " num2
    
    #Checking validity
    if ! [[ "$num1" =~ ^[0-9]+$ ]] && ! [[ "$num2" =~ ^[0-9]+$ ]] && [ "$num1" -eq 0 ] && [ "$num2" -eq 0 ]; then
        echo -e "Wrong arguments, please try again...\n"
        continue
    fi

    __gcd "$num1" "$num2"
done
