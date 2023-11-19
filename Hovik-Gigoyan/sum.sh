#!/bin/bash

if [ $# ne ] ; then
	echo "Usage: $0 <limit>"
	exit 1
fi

limit=$1
sum=0

while read -r number; do
  if [ -z "$number" ]; then
	break
  fi


  sum=$((sum + number))

  if [ $sum -ge $limit ]; then
	echo $sum
	exit 0
  fi
done

echo $sum
exit 0
