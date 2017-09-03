#!/usr/bin/sh

gcc -o life life.c
./life<<<4 >C_output
cat board1.s prog.s >life.s
spim -f life.s<<<4 >S_output
diff C_output S_output
