#/bin/bash


__gcd()
{

    local M="$1"
    local N="$2"

    if [ "$N" -eq 0 ]; then
	echo "GCD is $M"
    else
	__gcd "$N" "$((M % N))"
    fi

}


 while true; do
    read -p "First number -> " num1

    if  [ -z "$num1"  ];then
	echo "bye"
	exit 0
    fi

    read -p "Second number -> " num2

    if [ -z "$num2" ];then
	echo "bye"
	exit 0
    fi

    __gcd "$num1" "$num2"
done
