#include "../../src/class/dev/ast_arithmetic.hpp"
#include "../../src/implementation.hpp"
#include "../../src/ast_call.hpp"

FILE *yyin;
char *yytext;
int yylineno;

void process(char *result)
{
  if (nullptr == result)
    return;
  printf("%s\n", result);
  free(result);
}

void t_negation()
{
  process(negation("1"));
  process(negation("1.0"));
  process(negation("\'a\'"));
  process(negation("\"a\""));
  process(negation("true"));
  process(negation("false"));
  process(negation("random"));
  process(negation(nullptr));
}

void t_chg_sgn()
{
  process(chg_sign("0"));
  process(chg_sign("-0"));
  process(chg_sign("1"));
  process(chg_sign("-1"));
  process(chg_sign("0.0"));
  process(chg_sign("-0.0"));
  process(chg_sign("1.0"));
  process(chg_sign("-1.0"));
  
  process(chg_sign("\'a\'"));
  process(chg_sign("\"a\""));
  process(chg_sign("true"));
  process(chg_sign("false"));
  process(chg_sign("random"));
  process(chg_sign(nullptr));
}

int main()
{
  // t_negation();
  t_chg_sgn();
}