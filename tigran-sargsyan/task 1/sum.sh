#!/bin/bash

limit=$1
sum=0

while read num;
do
  sum=$((sum + num))
  if ((sum >= limit));
  then
    echo $sum
    exit 0
  fi
done

echo $sum
