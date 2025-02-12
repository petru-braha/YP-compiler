#include <iostream>
#include "../src/class/primitive_data.hpp"
#include "../src/class/function_data.hpp"
#include "../src/class/object_data.hpp"
#include "../src/class/array_data.hpp"
#include "../src/class/class_data.hpp"

#include "../src/class/symbol_table.hpp"
#include "../src/class/type_table.hpp"

#include "../src/ast_expression.hpp"
#include "../src/ast_definition.hpp"
#include "../src/ast_action.hpp"
#include "../src/ast_scope.hpp"
#include "../src/ast_control.hpp"

std::vector<symbol_table> symbols;
#define LAST_SCOPE symbols.size() - 1

void yyerror(const char *s)
{
  printf("error - line %d: %s.\n", __LINE__, s);
}

int main()
{
  mutable_data *primitive = new primitive_data(INTG_DATA_TYPE);

  typedef std::unordered_map<std::string, mutable_data *> map;
  map *arguments = new map;
  arguments->insert({{"number", primitive}});

  char buffer[] = "10";
  ast_statement *call = new ast_constant(buffer);
  std::vector<ast_statement *> *propositions =
      new std::vector<ast_statement *>;
  propositions->emplace_back(call);

  function_data *function =
      new function_data(INTG_DATA_TYPE, arguments, propositions);

  delete function;

  // end program:
  // there is no need of clearing manually data in parser
  // it will be done automatically
  // symbols.erase(symbols.begin(), symbols.end());
}

//todo make compiler not crash
//todo check if get_buffer is applied correctly

/* example
in the function body we define
assign global to the definition
the compiler says ok
at the end of function, local data is flushed
*/