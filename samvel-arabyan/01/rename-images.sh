#!/bin/bash

for var in *.jpg 
  do
  if [[ "$var" =~ [0-9]{4}-[0-9]{2}-[0-9]{2}-.*\.jpg  ]] 
  then
 echo "Skipping!" 
  else
creation_date=$(stat $var -c "%y" | awk '{print $1}')
new_name="${creation_date}-${var}"
mv ./${var} ./${new_name}
  fi
 
  done


