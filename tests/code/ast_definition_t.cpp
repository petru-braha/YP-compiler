#include "../../src/ast_definition.hpp"
#include "../../src/implementation.hpp"
#include "../../src/ast_call.hpp"
#include "../../src/ast_expression.hpp"

FILE *yyin;
char *yytext;
int yylineno;

int main()
{
  scope_insert();
  initialize_compiler();

  ast_statement *stat = new ast_primitivedefn(
      "int", "lmao",
      new ast_constant("10"));

  scope_remove();
  type_remove();
}