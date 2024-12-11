#!/bin/bash

if [ $# -ne 1 ] 
    then echo "error: please provide (just) one file to be analysed"
    exit 1
fi

rm -f lex.yy.cc
#rm -f $1.tab.c
#rm -f $1
bison -d YP_parser.ypp
lex YP_lexer.l
g++ lex.yy.cc  YP_parser.tab.cpp -o YP_executable

rm lex.yy.c
rm -f $1.tab.c
rm -f $1

#g++ SymTable.cpp lex.yy.cpp  $1.tab.c -o $1

echo "no fatal error found,"

# launch execution
