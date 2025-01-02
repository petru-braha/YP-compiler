# YP compiler

You can find the romanian version of this document [here](/docs/README%20RO.md).
Test-driven development principles were considered in this project.

## Usage (in project's root)

- for improved redability, we recommand VS Code and the "Better Comments" extension

0. "./setup.sh" - checks for bison and flex installation and builds our compiler
0. "./compile.sh" - builds the custom compiler
0. "./src/discard.sh" - delete the additional files
0. "./run.out <file_path>" - compiles and runs the source code

## Original features

- All variables/parameters/objects have:
    - explicit value(s)
    - implicit value(s) if there is no given definiton
        - e. g. 0, 0.0, '0', "", true
    - no container will ever be "undefined"

- x-dimensional arrays, where x could be any natural value not NULL. the same is assured for the size of each dimension.

- Recognize both int[1][3] variable_name and int variable_name[14][5151][62];

- Complex class declarations: see [implementation details](/docs/brainstorm.md)

## Limitations

- No type qualifiers
- No pointers or refferences
- No union, struct
- No casts
- No inheritence of classes (no protected access specifier)
- No method overloading

## To do

- the development is split in two segments:
    - declaration
        - recognition
        - synopsis
        - jumps
        - assignation
    - stataments
        - recursion
        - abstract syntax tree

0. who should take care of the error cases? utility or parser? it is confusing when errors are defined in both places
0. field access through object
0. const specifier, naming convetions

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

<br>

0. maybe we should not allow declarations of already defined symbols
0. complete romanian version of this document
0. multi line comment
0. complete the syntax documentation from the guidline
0. friend class std::pair - didn't work on a first try

