# YP compiler

You can find the romanian version of this document [here](/docs/README%20RO.md).

## Usage (in project's root)

- for improved redability, we recommand VS Code and the "Better Comments" extension

0. "./setup.sh" - checks for bison and flex installation and builds our compiler
0. "./compile.sh" - builds the custom compiler
0. "./src/discard.sh" - delete the additional files
0. "./run.out <file_path>" - compiles and runs the source code

## Features

- TDD - this project is a test-driven development

- C's main functions in our program is named master:
    - the program begins by calling master
    - master() doesn't return any value

- x-dimensional arrays, where x could be any natural value not NULL. the same is assured for the size of each dimension.

- NULL initialization of the data at declaration if the user doesn't provide an assignation

- Recognize both int[1][3] variable_name and int variable_name[14][5151][62];

## Limitations

- No pointers or refferences
- No union, struct definitions
- No casting feature
- No inheritence of classes(no protected access specifier)
- No method overloading

## Brainstorming

- Four possible data storage types:
    - class(type)
    - function
    - variable
    - object

- Three possible states of a data storage:
    - declaration
    - definition
    - call

- There is a major difference between declared and defined. We'll have to store both declarations and definitions and use them according to the appropriate scenario.

- There is a difference between variable and object. An object is created with the user's defined classes(types), meanwhile the variable's type can only be a reserved one.

- Functions can be declared at local scopes.

- Definition != assignation.

### schema

- variable's type is one of the reserved
- class = type
- definition of a variable/object = assignation (also created by default at declaration)

<br>

0. class declaration
1. field declaration
2. class definition (all fields definition)
3. object declaration
4. object definition
5. object call

<br>

0. function declaration
1. function definition
2. function call

<br>

0. variable declaration
1. variable definition
2. variable call

### type container

- class(type) declaration only at global scope
- stored when declared and defined
- data structure: map - O(1) search time for a S_NME

- reserved types:
    - int
    - float
    - char
    - string
    - bool

### symbol container

- scope depended
- stored when declared or defined
- data structure: map - O(1) search time for a S_NME

- symbol = function/variable/object
- struct symbol: name, item_type, data_type, synopsis(values)
- synopsis:
    - function - parameter list
    - variable - value
    - object - synopsis of its symbols

### guideline

- mapping of the type to:
    - string - 3 - 5 bytes for the already defined types but for class the number of bytes is user dependent
    - unsigned char - 1 byte always - allows the definition of 256-5 classes (not reliable)
    - unsigned short - 2 bytes always - 65.535-5 classes (is not too reliable)
    - unsigned int - 4 bytes always - allows 4,294,967,295 (could be reliable)

- declaration syntax:
    - class: class name_class;
    - function: 
        - list_parameter:
        - return_type name_function(list_parameter);
    - variable:
    - object:

- definition syntax:
    - class:
        - access specifiers
        - fields
        - name_class{ filed0, field1 }
    - function:
        - list_parameter:
        - return_type name_function(list_parameter);
    - variable:
    - object:

- call syntax:
    - class: - "={parameter_list}" if it's an object
    - function:
    - variable: - "=" if it has a reserved type
        - if not done, by default every field will the a NULL value
    - object:

### enconding of the values

- adding to union those types
- store type, values as std::string for each variable name
- synopsis for a function is an array of objects/variables

### standard methods

int a = 5;
string name = Type(a); 

- master
- Type
    - argument: name_of_something
    - return type: string
- Print
    - purpose: prints on terminal
    - argument: name_of_something | constant
    - return: number of bytes written
    - return type: int

## To do

- the development is split in two segments:
    - declaration
        - recognition
        - jumps
        - synopsis
        - assignation
    - stataments
        - recursion
        - abstract syntax tree

0. actual variable assignation
1. field access through object
2. ast - statament recognition and logic
2. complete the syntax documentation from the guidline

<br>

2. complete romanian version of this document
2. multi line comment

## MORE BRAINSTORM

- strdup => memory leaks!!!!!
- every time i call a function it is an assignation of its variable + code jumps; we can view it as a struct in C