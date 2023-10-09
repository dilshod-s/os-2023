#!/bin/bash

# if there is only one argument and it is the limit 
if [ $# -ne 1 ]; then
  echo "Limit is -> : $0"
  exit 1
fi

limit=$1
final_sum=0

# read arguments from standard input and sum them
while read -r number; do
  if ! [[ "$number" =~ ^[0-9]+$ ]]; then
    echo "\"$number\" is NaN"
    continue
  fi
  final_sum=$((final_sum + number))
  if [ $final_sum -ge $limit ]; then
    break
  fi
done

echo $final_sum

#to execute this we may use `echo -e "1\n20\n370\n987" | ./sum.sh 20` instead of `echo "1\n20\n370\n987" | ./sum.sh 20`,
#for recognizing newline characters.
