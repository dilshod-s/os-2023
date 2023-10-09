#!/bin/bash
limit=$1
for((sum=0;$sum < $limit ;))
do
 read num
let sum+=num
done

echo $sum
