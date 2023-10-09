#!/bin/bash

function Count(){
count=$(ls -1  $1 | wc -l)
echo $count
}
sum=$(Count $1)
echo $sum
