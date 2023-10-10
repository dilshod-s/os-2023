#!/bin/bash

read limit

for ((sum=0;$sum <limit ;))
do
 read num
let sum+=num
done

echo $sum
