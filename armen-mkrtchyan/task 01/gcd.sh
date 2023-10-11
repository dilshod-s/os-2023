#!/bin/bash

function gcd(){
    
    n=$1
    m=$2
    
    if [[ $n -gt $m ]]
       then
       let n-=$m
       gcd $n $m
    elif [[ $n -lt $m ]]
       then
       let m-=$n
       gcd $n $m
    else [[ $n == $m ]]
       echo  "GCD is "$n  
       return
    fi 
}

read n
read m
if [[ $n == "" || $m == "" ]]
   then 
   echo "bye"
   break
else
  gcd $n $m  
fi
