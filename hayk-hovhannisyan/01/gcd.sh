#!/bin/bash

 function GCD(){
  frst=$1
  sec=$2
if [[ $frst == $sec ]]
 then
  echo  "GCD is "$frst  
  return
elif [[ $frst -gt $sec ]]
 then
  let frst-=$sec
  GCD $frst $sec
elif [[ $frst -lt $sec ]]
 then
  let sec-=$frst
  GCD $frst $sec
fi 
}

while true
do
  read frst
if [[ $frst == "" ]]
then 
  echo "bye"
  break
else

  read sec
  GCD $frst $sec  
fi
done
