#!/bin/bash

function gcd() {
  if [[ $1 == $2 ]];
  then 
    echo "GCD is $1"
  elif [[ $1 -gt $2 ]];
  then 
    gcd $2 $(($1-$2))
  else
    gcd $(($2-$1)) $1
  fi
}

while true;
do
read N
read M
if [[ $N == "" || $M == "" ]];
then 
  echo "bye"
  break
elif [[ "$N" =~ ^[1-9][0-9]*$ && "$M" =~ ^[1-9][0-9]*$ ]];
then
  gcd $N $M
else 
  echo "not a natural number"
fi
done
