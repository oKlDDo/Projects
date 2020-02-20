#!/bin/bash

#compiles the code
gcc -o prog ${1}

#puts all arguments into a list
arguments=($@)

#determines the amount of arguments
length=0;
for n in ${arguments[@]:1}; do
    length=$((length+1));
done

#if length is less than one, there are not enough arguments 
if((length<1))
then
    echo "Invalid argument list. Not enough arguments are present."
    echo "Proper usage: script01 <path to source file> m1 [m2 [m3 [...]]]"
    exit 1
fi

#for each argument test to see if it is strictly a positive integer, if not, display error and exit
for i in ${arguments[@]:1};
do
    if (($i < 1))
    then
        echo "Invalid arguent list. All arguments should be strictly positive integers."
        echo "Proper usage: script01 <path to source file> m1 [m2 [m3 [...]]]"
        exit 1
    fi
done

#after all error checking run the program to get the divisors of each argument (except for name of program)
for i in ${arguments[@]:1};
do
    ./prog "$i"
done


#run the program to get the gcd of all of the arguments in the order they are presented
for ((j=1; j<=length; j++)); do
     for ((k=j+1;k<=length;k++)); do
             ./prog ${arguments[j]} ${arguments[k]}
     done
done 


