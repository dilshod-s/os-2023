#!/bin/bash

limit=$1
for((sum=0;$sum <limit ;))
do
 read tmp
let sum+=tmp
done

echo $sum
