#!/bin/bash

function gcd()
{
  elem1=$1
  elem2=$2 
  if [[ $elem1 == 0 || $elem2 == 0 ]]
  	then 
  	   echo "one of statements is 0"
  		return
  	fi
  if [[ $elem2 -gt $elem1 ]]
  	then 
  		temp=$elem1
  		  elem1=$elem2
  		 elem2=$temp
  	fi
  if [[ $((elem1 % elem2)) -eq 0 ]]
  	then 
  		echo $elem2 "Is GCD"
  		return
  else
  		let elem1%=$elem2
  		gcd $elem2 $elem1
  fi
} 

while true
do
  read num1
if [[ $num1 == "" ]]
then 
  echo " elem 1 is not number"
  break
else
  read num2
  gcd $num1 $num2  
fi
done
