# YP compiler


## Brainstorming

- lexer consumes input
- parser

## To do

0. parse types when operator see (1)
1. symbol table - no class declaration after scope_begin (more precisely if it is not closed)

## Features

- C's main functions in our program is named master
    - the program begins by calling master
    - master() doesn't return any value

- x-dimensional arrays, where x could be any natural, not null value

- class, function, and variable definitions
    - no union, struct definitions

- no pointers or refferences

## Usage (in project's root)

0. "./compile.sh" 
1. "./run.out <file_path>" - test if a source code has errors
2. "./src/discard.sh" - delete extra file
