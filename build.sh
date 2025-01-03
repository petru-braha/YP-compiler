#!/bin/bash

./src/discard.sh
bison -d YP_parser.ypp
lex YP_lexer.l
g++ -std=c++17 lex.yy.c YP_parser.tab.cpp -o run.out

rm -f lex.yy.c
rm -f YP_parser.tab.cpp
rm -f YP_parser.tab.hpp
