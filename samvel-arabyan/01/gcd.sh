#!/bin/bash

 function gcd(){
  first=$1
  second=$2
if [[ $first == $second ]]
 then
  echo  "GCD is "$first  
  return
elif [[ $first -gt $second ]]
 then
  let first-=$second
  gcd $first $second
elif [[ $first -lt $second ]]
 then
  let second-=$first
  gcd $first $second
fi 
}

while true
do
  read first
if [[ $first == "" ]]
then 
  echo "bye"
  break
else

  read second
  gcd $first $second  
fi
done
