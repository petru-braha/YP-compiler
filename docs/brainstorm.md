## To do

0. expression - add iden ,array support, operator[], access field
0. control statements
0. jump implementation, return

<br>

0. grammar conflicts
0. allow declarations of already defined symbols?
0. complete the syntax documentation from the guidline
0. better names: abbreviation capslock?
0. restrict access to type_table
0. multi line comment

## Brainstorming - general ideas

- each test which will be marked as "# works as expected"
- field declaration is done within the class, but its definition is inside the object

- fields: variables, functions (methods), objects
- attributes: variables, objects

- C's main functions in our program is named "master()":
    - does not take any arguments
    - the program begins by calling master
    - master() doesn't return any value

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

### guideline

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

- every time i call a function it is an assignation of its variable + code jumps; we can view it as a struct in C

## Order of error checking

### for declaration

* type_exists($1)
- is_type(id)
* is_type(argument)
- scope_search(id) || class_search(id) (not both)
* scope_search(argument)
* class_search(argument)

## Questions:

- friend class std::unordered_map<std::string, variable_data> does not work
- global syntax can't be declared after grammar
- auto error messages for constructors and insertions (specific methods) - who should take care of the error cases? utility or parser? it is confusing when errors are defined in both places. short answer in both places, the distinction is made wihtin the type of method: modifiable/interogative
- ids from scopes have priority before ids from the class definition

- what happens if error occurs? should we stop the execution?


- ++ constructors
class cacat
{

}

class apa
{
    int filed0;
    int field1;
    cacat object_apa;

public:
    apa() { field0 = 0; prinf("mata"); }
    apa(int, int, int) {}
}


apa object(1, 1, 2);
printf("tactu");


for(int i = 0 ; i < 10 ; i ++;)
for(auto i : container) == for(auto i = begin(); i != end(); i++)

i == iterator
*i == std::pair<std::string, item_data*>
(*i).second == 