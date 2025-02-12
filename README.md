# YP compiler

You can find the romanian version of this document [here](/docs/README%20RO.md).
Test-driven development principles were considered in this project.

## Usage

- for improved redability, we recommand VS Code and the "Better Comments" extension
- commands to be passed in project root terminal:

0. "./setup.sh" - checks for bison and flex installation and builds our compiler
0. "./build.sh" - builds the custom compiler
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

- Each file from [examples directory](/exs/) is responsable of one grammar rule.

- See [implementation details](/docs/brainstorm.md) for more.

- Default parameters for functions

## Limitations

- No type qualifiers
- No pointers, refferences
- No struct, union
- No inheritence of classes
