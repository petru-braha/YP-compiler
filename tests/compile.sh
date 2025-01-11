#!/bin/bash

bison -d parse.ypp
lex lexer.l
g++ -std=c++17 lex.yy.c parse.tab.cpp -o run.out

rm -f lex.yy.c
rm -f parse.tab.cpp
rm -f parse.tab.hpp
