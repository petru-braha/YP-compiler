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

- provide for each strdup() call the free() method => no memory leaks

- the development is split in two segments:
    - declaration
        - recognition
        - jumps
        - synopsis
        - assignation
    - stataments
        - recursion
        - abstract syntax tree

0. change to unordered map => average time complexity operations constant 
0. std::unordered_set or std::unordered_map??????????????????????????? NOT std::unordered_set less sugestive and practical 
0. object data constructors
1. tbh i don't want to add a name field for each symbol table (it's just useless...)
2. actual variable assignation
3. field access through object
4. ast - statament recognition and logic
5. complete the syntax documentation from the guidline

<br>

0. array support
1. operator[] 

<br>

2. complete romanian version of this document
2. multi line comment

