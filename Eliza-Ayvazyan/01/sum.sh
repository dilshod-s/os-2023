#!/bin/bash

limit=$1
sum=0

while read x
do
  let sum+=x

  if [[ $sum -ge $limit ]]
  then
    break
  fi
done

echo $sum

#echo -e "10\n20\n30" | ./sum.sh 25
