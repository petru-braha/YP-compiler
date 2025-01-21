#!/bin/bash

bison -d parser.ypp -Wcounterexamples
flex lexer.l
g++ -std=c++17 lex.yy.c parser.tab.cpp -o run.out

rm -f lex.yy.c
rm -f lex.yy.cc
rm -f parser.tab.c
rm -f parser.tab.h
rm -f parser.tab.cpp
rm -f parser.tab.hpp
