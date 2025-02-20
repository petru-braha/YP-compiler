#include "../../src/class/function_data.hpp"
#include "../../src/implementation.hpp"
#include "../../src/ast_call.hpp"

FILE *yyin;
char *yytext;
int yylineno;

int main()
{
  constexpr size_t COUNT_PARAMETER = 1024;

  function_data::map *arguments =
      new function_data::map;
  for (size_t i = 0; i < COUNT_PARAMETER; i++)
  {
    function_data::pair pair(
        function_data::default_id(arguments),
        new primitive_data("int"));
    arguments->insert(pair);
  }

  function_data data(
      "int", arguments,
      new std::vector<ast_statement *>());

  std::vector<mutable_data *> *values =
      new std::vector<mutable_data *>();
  values->reserve(COUNT_PARAMETER);
  for (size_t i = 0; i < COUNT_PARAMETER; i++)
    values->emplace_back(new primitive_data("int", "5"));

  data.call(values);
}