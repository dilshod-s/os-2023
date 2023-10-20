#!/bin/bash

for img in $(ls *.jpg)
do
    if [[ "$img" =~ [0-9]{4}-[0-9]{2}-[0-9]{2}-.*\.jpg  ]] 
       then
        echo "Skip"
    else
        temp=$(stat $img -c "%y" | awk '{print $1}') 
        mv ./${img} ./${temp}-${img}.jpg
    fi
    done
  

