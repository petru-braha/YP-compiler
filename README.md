# YP compiler


## Brainstorming

- any user defined type (classes) will be labeled as ITEM_TYPE_CLS
- data type increments for every class defined
    - for a variable data_type could be
        - int
        - float
        - char
        - string
        - bool
        - any class's name already defined (or maybe just declared ?)
    - for a function == return_type (any type as previously discussed)
    - for a class == 1 to 1 mapping - only the type(name) of the class

- mapping of the type to:
    - string - 3 - 5 bytes for the already defined types but for a class declaration 
    - unsigned int - 4 bytes always - allows 4,294,967,295
    - unsigned short - 65.535 - 5 classes
    - unsigned char - 1 byte always - allows the definition of 256 - 5 classes

0. declaration syntax
    - variable
    - function
    - class
1. definition syntax
2. initialization / calling
    - variable - "=" if it has a reserved type
    - class - "={parameter_list}" if it's an object
    - if not done, by default every field will the a NULL value

- synopsis
    - variable
        - name
        - value(s) - what if class with multiple values
    - function
        - return type
        - name
        - parameter list
    - class
        - synopsis of its variables
        - synopsis of its functions

- recognize both int[1][3] a; and int a[14][5151][62];

## To do

0. no class/function declaration/definition after scope_begin (more precisely if it is not closed)
1. don't use names not declared
2. parse types when operator see (1)
3. 

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




1. se citeste din codul sursa - bottom up parser
2. alege regulile din gramatica definita - bottom up parser
3. .ypp .y contine bottom up parser si gramatica

4. token
5. lexer
6. lexer => parser file

- parser file 
    - parsare

    
1. definire token, grammar
2. lexer citeste easy.txt si recunoaste
3. parser


- int variabla