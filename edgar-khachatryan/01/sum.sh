#!/bin/bash

limit=$1

sum=0

while read -r num
do
  if [ "$sum" -ge "$limit" ]
  then
    echo $sum
    exit 1
  fi
  ((sum=sum+num))
done

echo $sum
exit 0
