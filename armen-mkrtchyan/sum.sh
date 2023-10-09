#!/bin/bash

read my_limit
for (( sum=0; $sum < my_limit; ))

do
read num
let sum+=num
done

echo $sum
