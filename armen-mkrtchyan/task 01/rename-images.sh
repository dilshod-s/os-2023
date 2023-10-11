#!/bin/bash

for f_name in $(ls *.jpg)

 do
   tmp=$(stat $f_name -c "%y" | awk '{print $1}') 
   mv ./${f_name} ./${tmp}-${f_name}.jpg
   
done
