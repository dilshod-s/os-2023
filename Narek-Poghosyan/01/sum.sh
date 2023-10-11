#!/bin/bash

echo -n "Enter the limit: "
read limit
sum=0 # Initialize sum to zero

while [ $sum -lt $limit ]
do
    read -p "Enter a number: " number 
    sum=$((sum + number))
done

echo "Sum of numbers entered is: $sum"
exit 0
