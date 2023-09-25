#!/bin/bash

for var in $(ls *.jpg)
do
tmp=$(stat $var -c "%y" | awk '{print $1}') 
mv ./${var} ./${tmp}-${var}.jpg
done


