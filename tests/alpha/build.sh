#!/bin/bash

bison -d parse.ypp -Wcounterexamples
flex lexer.l
g++ -std=c++17 lex.yy.c parse.tab.cpp -o run.out

rm -f lex.yy.c
rm -f lex.yy.cc
rm -f parse.tab.c
rm -f parse.tab.h
rm -f parse.tab.cpp
rm -f parse.tab.hpp
