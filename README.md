# YP compiler

You can find the romanian version of this document [here](/docs/README%20RO.md).
Test-driven development principles were considered in this project.

## Usage

- for improved redability, we recommand VS Code and the "Better Comments" extension
- commands to be passed in project root terminal:

0. "./setup.sh" - checks for bison and flex installation and builds our compiler
0. "./compile.sh" - builds the custom compiler
0. "./src/discard.sh" - delete the additional files
0. "./run.out <file_path>" - compiles and runs the source code

## Technologies

0. C++
0. Flex
0. Yacc/Bison

## Features

- All variables/parameters/objects have:
    - explicit value(s)
    - implicit value(s) if there is no given definiton
        - e. g. 0, 0.0, '0', "", true
    - no container will ever be "undefined"

- x-dimensional arrays, where x could be any natural value not NULL. the same is assured for the size of each dimension.

- Recognize both int[1][3] variable_name and int variable_name[14][5151][62];

- Each file from [examples directory](/exs/) is responsable of one grammar rule.

- See [implementation details](/docs/brainstorm.md) for more.

## Limitations

- No type qualifiers
- No pointers or refferences
- No union, struct
- No casts
- No inheritence of classes (no protected access specifier)
- No method overloading

## To do

0. tests
0. grammar conflicts
0. assignation for object of object (etc)

<br>

0. jump implementation
0. define what syntacticly correct file means
0. statement recognition - be able to read any syntactic correct file
0. build ast
0. compilation of compiler
0. test cases

<br>

0. array support
0. operator[]
0. for now we are assuming that our classes work as C's "struct"s
0. add constructor constraint for classes

<br>

0. maybe we should not allow declarations of already defined symbols
0. complete romanian version of this document
0. multi line comment
0. complete the syntax documentation from the guidline
0. friend class std::pair - didn't work on a first try
0. abbreviation?
0. capslock?
0. restrict access to type_table
