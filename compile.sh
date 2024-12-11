#!/bin/bash

rm -f a.out
rm -f lex.yy.c
rm -f YP_parser.tab.cpp
rm -f YP_parser.tab.hpp
bison -d YP_parser.ypp
lex YP_lexer.l
g++ lex.yy.c YP_parser.tab.cpp
