## To do

0. char - operations? '\n'
0. complete the syntax documentation from the guidelines
0. better names: abbreviation capslock?

## General ideas

- function_data and class_data can be firstly declared and later defined

- compilation should never throw exceptions
- all data is encoded as string
 
- note to self: doing left recursion is alright: the base case is firstly evaluated (similar to right recursion)

- memory allocation -> parser
- memory deallocation -> ast, classes
- a scope either returs or breaks

- ids from scopes have priority before ids from the class definition
- for now no global declarations after master()
- ast for declaration too
- pass nullptr value for non-existant identifiers

- before: a scope = a symbol table
- after: a scope = an ast node with a symbol table

- four classes of data types:
    - RSV_TYPE - reserved type (the only one that supports arithmetic operators)
    - RSV_ARRY - an array of reserved type
    - SMT_NAME - user-defined type
    - DEF_ARRY - an array of user-defined type

- expression - RSV_TYPE
- statement - any type

- '-' unary operator for int only
- '!' unary operator for bool only
- expression can only be primitive and not array
- RSV_ARRY DEF_ARRY are correct sized by lexer
- error checking for a rule: for each element starting from left-most one
- exception: symbol table insertions won't provide error messages
- initializing an array of object - initialize every object the same
- each test which will be marked as "# works as expected"
- field declaration is done within the class, but its definition is inside the object

- fields: variables, functions (methods), objects
- attributes: variables, objects

- C's main functions in our program is named "master()":
    - does not take any arguments
    - the program begins by calling master
    - master() doesn't return any value

## Containers

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

- reserved types:
    - int
    - float
    - char
    - string
    - bool

### symbol container

- scope depended
- stored when declared or defined

- symbol = function/variable/object
- struct symbol: name, item_type, data_type, synopsis(values)
- synopsis:
    - function - parameter list
    - variable - value
    - object - synopsis of its symbols

## Guideline

- mapping of the type to:
    - string - 3 - 5 bytes for the already defined types but for class the number of bytes is user dependent
    - unsigned char - 1 byte always - allows the definition of 256-5 classes (not reliable)
    - unsigned short - 2 bytes always - 65.535-5 classes (is not too reliable)
    - unsigned int - 4 bytes always - allows 4,294,967,295 (could be reliable)

- data structure for symbols (analysis for searches, insertions, deletions):
    - std::unordered_map
        - average case constant
        - worst case linear
        - better than set: we don't have to create pairs
    - std::map
        - worst case logarithmic 
    - std::set
        - worst case logarithmic 
    - std::unordered_set
        - average case constant
        - worst case linear
    - std::vector
        - worst case linear

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

## Methods

int a = 5;
string name = Type(a); 

- master()
- Type
    - argument: name_of_something
    - return type: string
- Print()
    - purpose: prints on terminal
    - argument: variable_data
    - return: number of bytes written
    - return type: int

- every time i call a function it is an assignation of its variable + code jumps; we can view it as a struct in C

### for declaration

* type_exists($1)
- is_type(id)
* is_type(argument)
- symbol_exists(id) || class_search(id) (not both)
* symbol_exists(argument)
* class_search(argument)

## Files

level 3:
- src/class/dev/yyerror.hpp
- src/class/dev/symbol_data.hpp
- src/class/dev/function.hpp
- src/class/dev/ast.hpp
- src/class/dev/ast_alphabet.hpp
- src/class/dev/ast_arithmetic.hpp

level 2:
- src/class/variable_data.hpp
- src/class/function_data.hpp
- src/class/object_data.hpp
- src/class/array_data.hpp
- src/class/class_data.hpp
- src/class/symbol_table.hpp
- src/class/type_table.hpp

level 1:
- src/node.hpp
- src/implementation.hpp

level 0:
- build.sh
- lexer.l
- parse.ypp
- YP

- level 0 - grammar
    - summary(abstraction) of the compiler
    - readable code for new viewrs
    - types: const char*
- level 1 - implementation (intermediary code translation - ast)
    - types: std::vector, std::string (usage of high-level containers)
- level 2 - classes to easy manipulate the stack program
- level 3 - constants

## Errors

- query VS procedure (interogative/modifiable)
    - queries won't produce any error message compared to procedures
    - follow-up: procedures should be implemented at level 1

- if error occurs - compilation is delayed as much as possible
- the compiler should not throw or crash! (no errors)

## Operators

| class | operator | allowed types |
|:-----:|:--------:|:--------------|
| OPR0 | "+" | int float char string |
| OPR0 | "-" | int float char string |
| OPR0 | "&" | bool |
| OPR0 | "\|"| bool |
| OPR0 | "⊕" | bool |
| OPR0 | "=="| int float char string bool |
| OPR0 | "!="| int float char string bool |
| OPR0 | "<="| int float char string |
| OPR0 | "<" | int float char string |
| OPR0 | ">="| int float char string |
| OPR0 | ">" | int float char string |
| OPR1 | "*" | int float char |
| OPR1 | "/" | int float char |
| OPR1 | "%" | int char |
| OPR2 | "^" | int float char |
| OPRU | "!" | bool |
| OPRU | "-" | int float |
| OPRR | "=" | any |

## Abstract syntax trees

| class | statement type | return type | notes | 
|:-----:|:--------------:|:-----------:|:------|
| ast_constant | ast_expression | char* | primitive unit |
| ast_operator | ast_expression | char* | works only with primitive types |
| ast_assign | ast_expression | symbol_data* | - |
| | | |
| ast_symbolcall | ast_expression | symbol_data* | used to symbol_exists() an id |
| ast_methodcall | ast_expression | mutable_data* | as ast_return::evaluate() |
| ast_vanillacall | ast_expression | char* | methods already defined |
| | | |
| ast_indexing | ast_expression | array_data* | ? |
| ast_fielding | ast_expression | symbol_data* | ? |
| ast_fieldcall | ast_expression | mutable_data* | ? |
| | | |
| ast_primitivedefn | ast_definition | ast_defn* | - |
| ast_functiondefn | ast_definition | ast_defn* | - |
| ast_objectdefn | ast_definition | ast_defn* | - |
| ast_classdefn | ast_statement | class_data* | used to define symbols in user-defined class |
| ast_scopedefn | ast_statement | symbol_data* | used to define symbols in scopes |
| | | |
| ast_action | ast_statement | char | returns a single character |
| ast_return | ast_statement | mutable_data* | - |
| | | |
| ast_scope | ast_statement | char | list of statemets terminated by a ast_return |
| ast_scope_control | ast_statement | char | list of statemets terminated by a ast_return/ast_action |
| | | |
| ast_ifelse | ast_statement | *** | - |
| ast_while | ast_statement | *** | - |
| ast_for | ast_statement | *** | - |

- *** == any from above
- method == function

- ast_expression -> char* / symbol_data*

## Sugar syntax

- int a, b = 5, doua_zeci = 20;
- 1.000 - int | 1,0 - float

## Future development

- sugar syntax
- wide up the count of types allowed for the operators
- control() just one instruction or none
- global declaration after master
- the end of compilation creates a binary file which evaluates the ast at run time

