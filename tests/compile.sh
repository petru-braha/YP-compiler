#!/bin/bash

bison -d parse.ypp
lex lexer.l
g++ -std=c++17 lex.yy.c parse.tab.cpp -o run.out
./discard.sh