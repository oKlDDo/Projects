#!/bin/bash

#puts all arguments into a list
arguments=($@)
#doesnt include bash or script1.sh
#determines the amount of arguments
length=0;
for n in ${arguments[@]}; do
    length=$((length+1));
done

#if length is less than 1, no file path present, which exits after displaying error.
if((length < 1))
then
    echo "There is no argument for a file path."
    echo "Proper Usage: script1.sh <pathToFile>."
    exit 1
fi

#if length is more than 1, too many file paths (shoudl only take one), which exits after displaying error.
if((length > 1))
then
    echo "There are too many arguments."
    echo "Proper Usage: script1.sh <pathToFile>."
fi

#if length is == 1 it will do ls of the file path and grep "\.dat" gets all files with the extension .dat
ls ${arguments[length-1]}| grep "\.dat"
