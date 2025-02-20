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

void t_chg_sign()
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

// no more testing of nullptr
// no more testing of type missmatch
void t_add_vals()
{
  process(add_vals("0", "-0"));
  process(add_vals("1", "-1"));
  process(add_vals("5.95", "1.06"));
  process(add_vals("-5.95", "-1.06"));
  process(add_vals("-5.95", "1.06"));
  process(add_vals("-9", "0"));

  process(add_vals("\"\"", "\"\""));
  process(add_vals("\"a\"", "\"b\""));
  process(add_vals("\"a\"", "\"\""));
  process(add_vals("\"\"", "\"b\""));
}

void t_sub_vals()
{
  process(sub_vals("12", "4"));
  process(sub_vals("0.01", "1.0"));
  process(sub_vals("-6", "-5"));

  process(sub_vals("\"\"", "\"\""));
  process(sub_vals("\"\"", "\"b\""));
  process(sub_vals("\"a\"", "\"b\""));
  process(sub_vals("\"a\"", "\"\""));
  process(sub_vals("\"aaa\"", "\"aaa\""));
}

void t_and_or_vals()
{
  process(and_vals("true", "true"));
  process(and_vals("true", "false"));
  process(and_vals("false", "true"));
  process(and_vals("false", "false"));

  process(or__vals("true", "true"));
  process(or__vals("true", "false"));
  process(or__vals("false", "true"));
  process(or__vals("false", "false"));

  process(xor_vals("true", "true"));
  process(xor_vals("true", "false"));
  process(xor_vals("false", "true"));
  process(xor_vals("false", "false"));
}

// no more checking of numeric literals
// so no mul div pow

void t_cmp_vals()
{
  process(cmp_vals("\"a\"", EE_CHR, "\"b\""));
  process(cmp_vals("\"a\"", GS_CHR, "\"b\""));
  process(cmp_vals("\"a\"", LE_CHR, "\"b\""));

  process(cmp_vals("false", EE_CHR, "true"));
  process(cmp_vals("false", LS_CHR, "true"));
}

// works as expected
int main()
{
  // t_negation();
  // t_chg_sign();
  // t_add_vals();
  // t_sub_vals();
  // t_and_or_vals();
  t_cmp_vals();
}