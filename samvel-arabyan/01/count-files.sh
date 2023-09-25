#!/bin/bash

function COUNTER(){
cd $1 | ls -1 | wc -l
}

sum=$(COUNTER $1)
echo $sum
