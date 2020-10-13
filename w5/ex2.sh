#!/bin/bash
#echo $(($(tail -n 1 < file.txt) + 1)) >> file.txt # with race condition
# critical region here is the part where the file is accessed for writing (so, >> file.txt)

#without race condition
tempfile=$(mktemp ./file.XXXXXXXXX)
while true
do
  lockfile=./lockfile
  if ln -s $tempfile $lockfile ; then
    echo got it
    echo $(($(tail -n 1 < file.txt) + 1)) >> file.txt
    rm $lockfile
    break
  else
    echo ocupied
  fi
done
rm $tempfile
