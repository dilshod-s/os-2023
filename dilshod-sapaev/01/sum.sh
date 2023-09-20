#!/bin/bash

SUM=0

if [[ $# != 1 ]]
then
	echo "argument should be passed";
	exit 1;
fi

while [[ $SUM < $1 ]]
do
	read increment;
	if [[ $? != 0 ]]
	then
		exit 0
	fi
	let SUM+=increment;
	echo "Current sum: $SUM";
done

