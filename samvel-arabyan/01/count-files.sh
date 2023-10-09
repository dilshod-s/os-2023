#!/bin/bash

function COUNTER(){
ls -1 $1 | wc -l
}

sum=$(COUNTER $1)
echo $sum
