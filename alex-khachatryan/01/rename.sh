#!/bin/bash

for file in *.jpg
do

date=$(stat -c %w $file)

date=$(echo $date | cut -d' ' -f1)

name="${date}-${file}"
mv $file $name

done
