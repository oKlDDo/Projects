#!/bin/bash

gcc -o program ${1}
#puts all arguments into a list
arguments=($@)
#doesnt include bash or script1.sh#
#determines the amount of arguments
length=0;
for n in ${arguments[@]}; do
    length=$((length+1));
done

#if length is less than 1, no file path present, which exits after displaying error.
if((length < 2))
then
    echo "There is no argument for a file path."
    echo "Proper Usage: script1.sh <pathToProgram> <pathToFile>."
    exit 1
fi

 #if length is more than 1, too many file paths (shoudl only take one), which exits after displaying error.
if((length > 2))
then
    echo "There are too many arguments."
    echo "Proper Usage: script1.sh <pathToProgram> <pathToFile>."
fi

#put all dat files found into a variable called dat
allDat=`ls ${2}/*.dat`
#making image list to put all the values into
imageValues=""
#using dat go through all the files and put them into imagelist so that all the coordinates and locaiton names are listed in imagelist
for file in $allDat; do
    contents=`cat $file`
    imageValues="$imageValues $contents"
done

#echo $imagelist
#runs them using prog
./program $imagelist
