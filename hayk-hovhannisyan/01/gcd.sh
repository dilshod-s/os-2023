#!/bin/bash

 function GCD(){
  a=$1
  b=$2
if [[ $a == $b ]]
 then
  echo  "GCD is " $a  
  return
elif [[ $a -gt $b ]]
 then
  let a-=$b
  GCD $a $b
elif [[ $a -lt $b ]]
 then
  let b-=$a
  GCD $a $b
fi 
}

while true
do
  read a
if [[ $a == "" ]]
then 
  echo "bye"
  break
else
  read b
  GCD $a $b  
fi
done
