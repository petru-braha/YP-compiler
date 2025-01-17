#ifndef __0ARIT0__
#define __0ARIT0__

/* comments:
 * there are 16 operation
 * the following methods will:
 ** validate parameters
 ** validate their data type
 ** return a heap allocated result
 * listed after the operator precedence
 */

#include <stdlib.h>
#include <string.h>
#include <string>

constexpr size_t BO_COUNT_DIGIT = 6;
constexpr size_t LL_COUNT_DIGIT = 20;

void yyerror(const char *);
std::string type_of(const std::string &primitive_value);

const char *negation(const char *v0);
const char *chg_sign(const char *v0);
const char *add_vals(const char *v0, const char *v1);
const char *sub_vals(const char *v0, const char *v1);
const char *and_vals(const char *v0, const char *v1);
const char *or__vals(const char *v0, const char *v1);
const char *mul_vals(const char *v0, const char *v1);
const char *div_vals(const char *v0, const char *v1);
const char *mod_vals(const char *v0, const char *v1);
const char *pow_vals(const char *v0, const char *v1);
const char *eq__vals(const char *v0, const char *v1);
const char *neq_vals(const char *v0, const char *v1);
const char *loe_vals(const char *v0, const char *v1);
const char *les_vals(const char *v0, const char *v1);
const char *goe_vals(const char *v0, const char *v1);
const char *grt_vals(const char *v0, const char *v1);

const char *negation(const char *v0)
{
  if (nullptr == v0)
  {
    yyerror("negation() failed - received nullptr");
    return nullptr;
  }

  if (std::string("bool") != type_of(v0))
  {
    yyerror("negation() failed - type missmatch");
    return nullptr;
  }

  // success
  char *result = (char *)malloc(BO_COUNT_DIGIT);
  if ('t' == v0[0])
    strcpy(result, "false");
  else
    strcpy(result, "true");

  return result;
}

const char *chg_sign(const char *v0)
{
  if (nullptr == v0)
  {
    yyerror("chg_sign() failed - received nullptr");
    return nullptr;
  }

  std::string type = type_of(v0);
  if (0 == strcmp("bool", type.c_str()) ||
      0 == strcmp("string", type.c_str()))
  {
    yyerror("chg_sign() failed - type missmatch");
    return nullptr;
  }

  // success
  char *result = (char *)malloc(LL_COUNT_DIGIT);
  result[0] = '-';
  return strcpy(result + 1, v0);
}

const char *add_vals(const char *v0, const char *v1);
const char *sub_vals(const char *v0, const char *v1);
const char *and_vals(const char *v0, const char *v1);
const char *or__vals(const char *v0, const char *v1);
const char *mul_vals(const char *v0, const char *v1);
const char *div_vals(const char *v0, const char *v1);
const char *mod_vals(const char *v0, const char *v1);
const char *pow_vals(const char *v0, const char *v1);
const char *eq__vals(const char *v0, const char *v1);
const char *neq_vals(const char *v0, const char *v1);
const char *loe_vals(const char *v0, const char *v1);
const char *les_vals(const char *v0, const char *v1);
const char *goe_vals(const char *v0, const char *v1);
const char *grt_vals(const char *v0, const char *v1);

#endif
