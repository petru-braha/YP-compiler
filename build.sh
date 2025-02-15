#!/bin/bash

bison -d YP_parser.ypp -Wcounterexamples
lex YP_lexer.l
g++ -std=c++17 lex.yy.c YP_parser.tab.cpp -o YP

rm -f *.yy.c
rm -f *.tab.cpp
rm -f *.tab.hpp
