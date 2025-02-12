#!/bin/bash

./src/discard.sh
bison -d parse.ypp
lex lexer.l
g++ -std=c++17 lex.yy.c parse.tab.cpp -o YP

rm -f lex.yy.c
rm -f *.tab.cpp
rm -f *.tab.hpp
