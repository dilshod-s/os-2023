#!/bin/bash

for name in $(ls *.jpg)
do
data=$(stat $name -c "%y" | awk '{print $1}') 
mv ./${name} ./${data}-${name}
done

