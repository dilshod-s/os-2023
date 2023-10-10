#!/bin/bash

gcd() {
  local M=$1
  local N=$2

  if [ $M -eq $N ]; 
  then
    echo "gcd is $M"
    
  elif [ $M -gt $N ]; 
  then
    gcd $((M - N)) $N
    
  else
    gcd $M $((N - M))
  fi
}

echo "write your number"

while true; 
do
  read -p "first num: " num1
  read -p "secind num: " num2

    if [ -z "$num1" ] || [ -z "$num2" ]; 
    then
      echo "bye"
      exit 0
    fi

    if ! [[ "$num1" =~ ^[0-9]+$ ]] || ! [[ "$num2" =~ ^[0-9]+$ ]] || [ "$num1" -eq 0 ] || [ "$num2" -eq 0  ]; 
    then
      echo "error"
      continue
    fi

  gcd $num1 $num2
done

