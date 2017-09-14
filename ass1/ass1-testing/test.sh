#!/bin/sh

echo "Testing board1.h and board1.s..."
passed=1
for i in `seq 6 2 100`
do
    gcc -std=c99 -o life life.c
    ./life<<<$i >c_output
    cat board1.s prog.s >life.s
    spim -f life.s<<<$i >s_output
    sed -i.bak -e '1d' s_output
    if ! diff s_output c_output
    then
        echo "$i: Not Cool"
        $passed=0
    fi
    rm -f s_output c_output s_output.bak
done
if [ $passed -eq 1 ] 
then 
    echo "Passed All"
fi
