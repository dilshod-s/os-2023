#!/bin/bash
lim=$1
for((sum=0;$sum < lim ;))
do
 read num
let sum+=num
done

echo $sum
