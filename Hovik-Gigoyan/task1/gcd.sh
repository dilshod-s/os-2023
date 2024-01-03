#!/bin/bash

gcd() {
    local m=$1
    local n=$2

    while [ $m -ne $n ]; do
        if [ $m -gt $n ]; then
            m=$(($m - $n))
        else
            n=$(($n - $m))
        fi
    done

    echo "$m"
}

while true; do
    read input

    if [[ -z $input ]]; then
        echo "bye"
        break
    fi

    read m n <<< $input

    gcd $m $n
done
