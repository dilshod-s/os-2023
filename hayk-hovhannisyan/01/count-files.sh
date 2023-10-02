#!/bin/bash


function Count(){
cd $1 | ls -1 | wc -l
}

sum=$(Count $1)
echo $sum
