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
#include <limits.h>
#include <cmath>
#include <string>
#include "alphabet.hpp"

constexpr size_t BO_COUNT_DIGIT = 6;
constexpr size_t LL_COUNT_DIGIT = 20;

void yyerror(const char *);
std::string type_of(const std::string &primitive_value);

char *negation(const char *const);
char *chg_sign(const char *const);
char *add_vals(const char *const, const char *const);
char *sub_vals(const char *const, const char *const);
char *and_vals(const char *const, const char *const);
char *or__vals(const char *const, const char *const);
char *xor_vals(const char *const, const char *const);
char *mul_vals(const char *const, const char *const);
char *div_vals(const char *const, const char *const);
char *mod_vals(const char *const, const char *const);
char *pow_vals(const char *const, const char *const);
char *cmp_vals(const char *const, const char *const);

//------------------------------------------------

char *negation(const char *const v0)
{
  if (nullptr == v0)
  {
    yyerror("negation() failed - received nullptr");
    return nullptr;
  }

  std::string type = type_of(v0);
  if (strcmp(type.c_str(), "bool"))
  {
    yyerror("negation() failed - wrong type");
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

char *chg_sign(const char *const v0)
{
  if (nullptr == v0)
  {
    yyerror("chg_sign() failed - received nullptr");
    return nullptr;
  }

  std::string type = type_of(v0);
  if (strcmp("int", type.c_str()) &&
      strcmp("float", type.c_str()))
  {
    yyerror("chg_sign() failed - wrong type");
    return nullptr;
  }

  // success
  char *result = (char *)malloc(LL_COUNT_DIGIT);
  if ('-' == v0[0])
    return strcpy(result, v0 + 1);

  result[0] = '-';
  return strcpy(result + 1, v0);
}

//------------------------------------------------

char *add_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1)
  {
    yyerror("add_vals() failed - received nullptr");
    return nullptr;
  }

  std::string frst_type = type_of(v0);
  std::string scnd_type = type_of(v1);
  if (frst_type != scnd_type)
  {
    yyerror("add_vals() failed - type missmatch");
    return nullptr;
  }

  if (0 == strcmp("bool", frst_type.c_str()))
  {
    yyerror("add_vals() failed - wrong type");
    return nullptr;
  }

  // success
  std::string result;
  if (0 == strcmp(frst_type.c_str(), "int"))
    result = std::to_string(atoll(v0) + atoll(v1));
  else if (0 == strcmp(frst_type.c_str(), "float"))
    result = std::to_string(atof(v0) + atof(v1));
  else if (0 == strcmp(frst_type.c_str(), "char"))
    result = std::to_string(
        (atoll(v0) % UCHAR_MAX + atoll(v1) % UCHAR_MAX) %
        UCHAR_MAX);
  else if (0 == strcmp(frst_type.c_str(), "string"))
  {
    result = v0;
    result.pop_back();
    result += (v1 + 1);
  }

  return strdup(result.c_str());
}

char *sub_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1)
  {
    yyerror("sub_vals() failed - received nullptr");
    return nullptr;
  }

  std::string frst_type = type_of(v0);
  std::string scnd_type = type_of(v1);
  if (frst_type != scnd_type)
  {
    yyerror("sub_vals() failed - type missmatch");
    return nullptr;
  }

  if (0 == strcmp("bool", frst_type.c_str()))
  {
    yyerror("sub_vals() failed - wrong type");
    return nullptr;
  }

  // success
  std::string result;
  if (0 == strcmp(frst_type.c_str(), "int"))
    result = std::to_string(atoll(v0) - atoll(v1));
  else if (0 == strcmp(frst_type.c_str(), "float"))
    result = std::to_string(atof(v0) - atof(v1));
  else if (0 == strcmp(frst_type.c_str(), "char"))
    result = std::to_string(atoll(v0) % UCHAR_MAX -
                            atoll(v1) % UCHAR_MAX);
  else if (0 == strcmp(frst_type.c_str(), "string"))
  {
    size_t position = 0;
    std::string text(v0 + 1), token(v1 + 1);
    text.pop_back();
    token.pop_back();
    while (std::string::npos !=
           (position = text.find(token, position)))
      text.erase(position, token.length());
    ((result += "\"") += text) += "\"";
  }

  return strdup(result.c_str());
}

//------------------------------------------------

char *and_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1)
  {
    yyerror("and_vals() failed - received nullptr");
    return nullptr;
  }

  std::string frst_type = type_of(v0);
  std::string scnd_type = type_of(v1);
  if (frst_type != scnd_type)
  {
    yyerror("and_vals() failed - type missmatch");
    return nullptr;
  }

  if (strcmp("bool", frst_type.c_str()))
  {
    yyerror("and_vals() failed - wrong type");
    return nullptr;
  }

  // success
  if (0 == strcmp(v0, "false") ||
      0 == strcmp(v1, "false"))
    return strdup("false");
  return strdup("true");
}

char *or__vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1)
  {
    yyerror("or_vals() failed - received nullptr");
    return nullptr;
  }

  std::string frst_type = type_of(v0);
  std::string scnd_type = type_of(v1);
  if (frst_type != scnd_type)
  {
    yyerror("or_vals() failed - type missmatch");
    return nullptr;
  }

  if (strcmp("bool", frst_type.c_str()))
  {
    yyerror("or_vals() failed - wrong type");
    return nullptr;
  }

  // success
  if (0 == strcmp(v0, "true") ||
      0 == strcmp(v1, "true"))
    return strdup("true");
  return strdup("false");
}

char *xor_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1)
  {
    yyerror("xor_vals() failed - received nullptr");
    return nullptr;
  }

  std::string frst_type = type_of(v0);
  std::string scnd_type = type_of(v1);
  if (frst_type != scnd_type)
  {
    yyerror("xor_vals() failed - type missmatch");
    return nullptr;
  }

  if (strcmp("bool", frst_type.c_str()))
  {
    yyerror("xor_vals() failed - wrong type");
    return nullptr;
  }

  // success
  if (strcmp(v0, v1))
    return strdup("true");
  return strdup("false");
}

//------------------------------------------------

char *mul_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1)
  {
    yyerror("mul_vals() failed - received nullptr");
    return nullptr;
  }

  std::string frst_type = type_of(v0);
  std::string scnd_type = type_of(v1);
  if (frst_type != scnd_type)
  {
    yyerror("mul_vals() failed - type missmatch");
    return nullptr;
  }

  if (0 == strcmp("bool", frst_type.c_str()) ||
      0 == strcmp("string", frst_type.c_str()))
  {
    yyerror("mul_vals() failed - wrong type");
    return nullptr;
  }

  // success
  std::string result;
  if (0 == strcmp(frst_type.c_str(), "int"))
    result = std::to_string(atoll(v0) * atoll(v1));
  else if (0 == strcmp(frst_type.c_str(), "float"))
    result = std::to_string(atof(v0) * atof(v1));
  else if (0 == strcmp(frst_type.c_str(), "char"))
    result = std::to_string(
        (atoll(v0) % UCHAR_MAX * atoll(v1) % UCHAR_MAX) %
        UCHAR_MAX);
  return strdup(result.c_str());
}

char *div_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1)
  {
    yyerror("div_vals() failed - received nullptr");
    return nullptr;
  }

  std::string frst_type = type_of(v0);
  std::string scnd_type = type_of(v1);
  if (frst_type != scnd_type)
  {
    yyerror("div_vals() failed - type missmatch");
    return nullptr;
  }

  if (0 == strcmp("bool", frst_type.c_str()) ||
      0 == strcmp("string", frst_type.c_str()))
  {
    yyerror("div_vals() failed - wrong type");
    return nullptr;
  }

  // success
  std::string result;
  if (0 == strcmp(frst_type.c_str(), "int"))
    result = std::to_string(atoll(v0) / atoll(v1));
  else if (0 == strcmp(frst_type.c_str(), "float"))
    result = std::to_string(atof(v0) / atof(v1));
  else if (0 == strcmp(frst_type.c_str(), "char"))
    result = std::to_string(
        (atoll(v0) % UCHAR_MAX / atoll(v1) % UCHAR_MAX) %
        UCHAR_MAX);
  return strdup(result.c_str());
}

//------------------------------------------------

char *mod_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1)
  {
    yyerror("mod_vals() failed - received nullptr");
    return nullptr;
  }

  std::string frst_type = type_of(v0);
  std::string scnd_type = type_of(v1);
  if (frst_type != scnd_type)
  {
    yyerror("mod_vals() failed - type missmatch");
    return nullptr;
  }

  // no float
  if (strcmp("int", frst_type.c_str()) &&
      strcmp("char", frst_type.c_str()))
  {
    yyerror("mod_vals() failed - wrong type");
    return nullptr;
  }

  // success
  std::string result;
  if (0 == strcmp(frst_type.c_str(), "int"))
    result = std::to_string(atoll(v0) / atoll(v1));
  else if (0 == strcmp(frst_type.c_str(), "float"))
    result = std::to_string(atof(v0) / atof(v1));
  else if (0 == strcmp(frst_type.c_str(), "char"))
    result = std::to_string(
        (atoll(v0) % UCHAR_MAX / atoll(v1) % UCHAR_MAX) %
        UCHAR_MAX);
  return strdup(result.c_str());
}

char *pow_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1)
  {
    yyerror("pow_vals() failed - received nullptr");
    return nullptr;
  }

  std::string frst_type = type_of(v0);
  std::string scnd_type = type_of(v1);
  if (frst_type != scnd_type)
  {
    yyerror("pow_vals() failed - type missmatch");
    return nullptr;
  }

  if (0 == strcmp("bool", frst_type.c_str()) ||
      0 == strcmp("string", frst_type.c_str()))
  {
    yyerror("pow_vals() failed - wrong type");
    return nullptr;
  }

  // success
  std::string result;
  if (0 == strcmp(frst_type.c_str(), "int"))
    result = std::to_string(
        (long long)std::pow(atoll(v0), atoll(v1)));
  else if (0 == strcmp(frst_type.c_str(), "float"))
    result = std::to_string(
        std::pow(atof(v0), atof(v1)));
  /*else if (0 == strcmp(frst_type.c_str(), "char"))
    result = std::to_string(
        std::pow(atoll(v0) % UCHAR_MAX, atoll(v1) % UCHAR_MAX));
  */
  return strdup(result.c_str());
}

char *cmp_vals(const char *const v0, const char op,
               const char *const v1)
{
  if (nullptr == v0 || nullptr == v1)
  {
    yyerror("cmp_vals() failed - received nullptr");
    return nullptr;
  }

  std::string frst_type = type_of(v0);
  std::string scnd_type = type_of(v1);
  if (frst_type != scnd_type)
  {
    yyerror("cmp_vals() failed - type missmatch");
    return nullptr;
  }

  std::string value0(v0), value1(v1);
  if (EE_CHR == op)
    return value0 == value1 ? strdup("true") : strdup("false");
  else if (NE_CHR == op)
    return value0 != value1 ? strdup("true") : strdup("false");
  else if (LE_CHR == op)
    return value0 <= value1 ? strdup("true") : strdup("false");
  else if (LS_CHR == op)
    return value0 < value1 ? strdup("true") : strdup("false");
  else if (GE_CHR == op)
    return value0 >= value1 ? strdup("true") : strdup("false");
  else if (GS_CHR == op)
    return value0 > value1 ? strdup("true") : strdup("false");

  return strdup("false");
}

#endif
