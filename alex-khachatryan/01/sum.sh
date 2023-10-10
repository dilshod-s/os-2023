#!/bin/bash

limit=$1
sum=0

while [[ sum -le limit  ]]
	do read number
	let sum+=number
	done


echo $sum

