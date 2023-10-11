#!/bin/bash

for img in $(ls *.jpg)
do
temp=$(stat $img -c "%y" | awk '{print $1}') 
mv ./${var} ./${temp}-${img}.jpg
done


