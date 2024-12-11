#!/bin/bash

echo "compiling $1"
rm -f lex.yy.c
rm -f $1
lex $1.l
gcc lex.yy.c -o $1
