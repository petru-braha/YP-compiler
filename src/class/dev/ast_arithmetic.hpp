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
#include "constexpr.hpp"
#include "function.hpp"
#include "yyerror.hpp"
#include "ast_alphabet.hpp"

constexpr size_t BO_COUNT_DIGIT = 6;
constexpr size_t LL_COUNT_DIGIT = 20;
constexpr char BOOL_LITERAL_0[] = "false";
constexpr char BOOL_LITERAL_1[] = "true";
constexpr char DIGITS[] = "0123456789";

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
char *cmp_vals(const char *const, const char,
               const char *const);

bool is_valid(const char *const v)
{
  if (v[0] == '-')
    return true;
  if (v[0] == '\'')
    return true;
  if (v[0] == '\"')
    return true;
  if (strchr(DIGITS, v[0]))
    return true;
  if (0 == strcmp(v, BOOL_LITERAL_0))
    return true;
  if (0 == strcmp(v, BOOL_LITERAL_1))
    return true;
  return false;
}

//------------------------------------------------

char *negation(const char *const v0)
{
  if (nullptr == v0 || false == is_valid(v0))
  {
    yyerror("negation() failed - received nullptr");
    return nullptr;
  }

  std::string type = type_of(v0);
  if (strcmp(type.c_str(), BOOL_DATA_TYPE))
  {
    yyerror("negation() failed - wrong type");
    return nullptr;
  }

  // success
  char *result = (char *)malloc(BO_COUNT_DIGIT);
  if ('t' == v0[0])
    return strcpy(result, BOOL_LITERAL_0);
  return strcpy(result, BOOL_LITERAL_1);
}

char *chg_sign(const char *const v)
{
  if (nullptr == v || false == is_valid(v))
  {
    yyerror("chg_sign() failed - received nullptr");
    return nullptr;
  }

  std::string type = type_of(v);
  if (strcmp(INTG_DATA_TYPE, type.c_str()) &&
      strcmp(FLOT_DATA_TYPE, type.c_str()))
  {
    yyerror("chg_sign() failed - wrong type");
    return nullptr;
  }

  // success
  char *result = (char *)malloc(LL_COUNT_DIGIT);

  // if v == 0
  if ('0' == v[0] && '\0' == v[1])
    return strcpy(result, v);
  if ('0' == v[0] && '.' == v[1])
  {
    bool zero = true;
    for (size_t i = 2; v[i] && zero; i++)
      if ('0' != v[i])
        zero = false;
    if (zero)
      return strcpy(result, v);
  }

  if ('-' == v[0])
    return strcpy(result, v + 1);

  result[0] = '-';
  result[1] = '\0';
  return strcat(result, v);
}

//------------------------------------------------

char *add_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1 ||
      false == is_valid(v0) || false == is_valid(v1))
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

  if (0 == strcmp(BOOL_DATA_TYPE, frst_type.c_str()))
  {
    yyerror("add_vals() failed - wrong type");
    return nullptr;
  }

  // success
  std::string result;
  if (0 == strcmp(frst_type.c_str(), INTG_DATA_TYPE))
    result = std::to_string(atoll(v0) + atoll(v1));
  else if (0 == strcmp(frst_type.c_str(), FLOT_DATA_TYPE))
    result = std::to_string(atof(v0) + atof(v1));
  else if (0 == strcmp(frst_type.c_str(), CHAR_DATA_TYPE))
    result = std::to_string(
        (atoll(v0) % UCHAR_MAX + atoll(v1) % UCHAR_MAX) %
        UCHAR_MAX);
  else if (0 == strcmp(frst_type.c_str(), STRG_DATA_TYPE))
  {
    result = v0;
    result.pop_back();
    result += (v1 + 1);
  }

  return strdup(result.c_str());
}

char *sub_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1 ||
      false == is_valid(v0) || false == is_valid(v1))
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

  if (0 == strcmp(BOOL_DATA_TYPE, frst_type.c_str()))
  {
    yyerror("sub_vals() failed - wrong type");
    return nullptr;
  }

  // success
  std::string result;
  if (0 == strcmp(frst_type.c_str(), INTG_DATA_TYPE))
    result = std::to_string(atoll(v0) - atoll(v1));
  else if (0 == strcmp(frst_type.c_str(), FLOT_DATA_TYPE))
    result = std::to_string(atof(v0) - atof(v1));
  else if (0 == strcmp(frst_type.c_str(), CHAR_DATA_TYPE))
    result = std::to_string(atoll(v0) % UCHAR_MAX -
                            atoll(v1) % UCHAR_MAX);
  else if (0 == strcmp(frst_type.c_str(), STRG_DATA_TYPE))
  {
    size_t position = 0;
    std::string text(v0 + 1), token(v1 + 1);
    text.pop_back();
    token.pop_back();
    if (text.size() && token.size()) // patch
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
  if (nullptr == v0 || nullptr == v1 ||
      false == is_valid(v0) || false == is_valid(v1))
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

  if (strcmp(BOOL_DATA_TYPE, frst_type.c_str()))
  {
    yyerror("and_vals() failed - wrong type");
    return nullptr;
  }

  // success
  if (0 == strcmp(v0, BOOL_LITERAL_0) ||
      0 == strcmp(v1, BOOL_LITERAL_0))
    return strdup(BOOL_LITERAL_0);
  return strdup(BOOL_LITERAL_1);
}

char *or__vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1 ||
      false == is_valid(v0) || false == is_valid(v1))
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

  if (strcmp(BOOL_DATA_TYPE, frst_type.c_str()))
  {
    yyerror("or_vals() failed - wrong type");
    return nullptr;
  }

  // success
  if (0 == strcmp(v0, BOOL_LITERAL_1) ||
      0 == strcmp(v1, BOOL_LITERAL_1))
    return strdup(BOOL_LITERAL_1);
  return strdup(BOOL_LITERAL_0);
}

char *xor_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1 ||
      false == is_valid(v0) || false == is_valid(v1))
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

  if (strcmp(BOOL_DATA_TYPE, frst_type.c_str()))
  {
    yyerror("xor_vals() failed - wrong type");
    return nullptr;
  }

  // success
  if (strcmp(v0, v1))
    return strdup(BOOL_LITERAL_1);
  return strdup(BOOL_LITERAL_0);
}

//------------------------------------------------

char *mul_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1 ||
      false == is_valid(v0) || false == is_valid(v1))
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

  if (0 == strcmp(BOOL_DATA_TYPE, frst_type.c_str()) ||
      0 == strcmp(STRG_DATA_TYPE, frst_type.c_str()))
  {
    yyerror("mul_vals() failed - wrong type");
    return nullptr;
  }

  // success
  std::string result;
  if (0 == strcmp(frst_type.c_str(), INTG_DATA_TYPE))
    result = std::to_string(atoll(v0) * atoll(v1));
  else if (0 == strcmp(frst_type.c_str(), FLOT_DATA_TYPE))
    result = std::to_string(atof(v0) * atof(v1));
  else if (0 == strcmp(frst_type.c_str(), CHAR_DATA_TYPE))
    result = std::to_string(
        (atoll(v0) % UCHAR_MAX * atoll(v1) % UCHAR_MAX) %
        UCHAR_MAX);
  return strdup(result.c_str());
}

char *div_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1 ||
      false == is_valid(v0) || false == is_valid(v1))
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

  if (0 == strcmp(BOOL_DATA_TYPE, frst_type.c_str()) ||
      0 == strcmp(STRG_DATA_TYPE, frst_type.c_str()))
  {
    yyerror("div_vals() failed - wrong type");
    return nullptr;
  }

  // success
  std::string result;
  if (0 == strcmp(frst_type.c_str(), INTG_DATA_TYPE))
    result = std::to_string(atoll(v0) / atoll(v1));
  else if (0 == strcmp(frst_type.c_str(), FLOT_DATA_TYPE))
    result = std::to_string(atof(v0) / atof(v1));
  else if (0 == strcmp(frst_type.c_str(), CHAR_DATA_TYPE))
    result = std::to_string(
        (atoll(v0) % UCHAR_MAX / atoll(v1) % UCHAR_MAX) %
        UCHAR_MAX);
  return strdup(result.c_str());
}

//------------------------------------------------

char *mod_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1 ||
      false == is_valid(v0) || false == is_valid(v1))
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
  if (strcmp(INTG_DATA_TYPE, frst_type.c_str()) &&
      strcmp(CHAR_DATA_TYPE, frst_type.c_str()))
  {
    yyerror("mod_vals() failed - wrong type");
    return nullptr;
  }

  // success
  std::string result;
  if (0 == strcmp(frst_type.c_str(), INTG_DATA_TYPE))
    result = std::to_string(atoll(v0) / atoll(v1));
  else if (0 == strcmp(frst_type.c_str(), CHAR_DATA_TYPE))
    result = std::to_string(
        (atoll(v0) % UCHAR_MAX / atoll(v1) % UCHAR_MAX) %
        UCHAR_MAX);
  return strdup(result.c_str());
}

char *pow_vals(const char *const v0, const char *const v1)
{
  if (nullptr == v0 || nullptr == v1 ||
      false == is_valid(v0) || false == is_valid(v1))
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

  if (0 == strcmp(BOOL_DATA_TYPE, frst_type.c_str()) ||
      0 == strcmp(STRG_DATA_TYPE, frst_type.c_str()))
  {
    yyerror("pow_vals() failed - wrong type");
    return nullptr;
  }

  // success
  std::string result;
  if (0 == strcmp(frst_type.c_str(), INTG_DATA_TYPE))
    result = std::to_string(
        (long long)std::pow(atoll(v0), atoll(v1)));
  else if (0 == strcmp(frst_type.c_str(), FLOT_DATA_TYPE))
    result = std::to_string(
        std::pow(atof(v0), atof(v1)));
  /*else if (0 == strcmp(frst_type.c_str(), CHAR_DATA_TYPE))
    result = std::to_string(
        std::pow(atoll(v0) % UCHAR_MAX, atoll(v1) % UCHAR_MAX));
  */
  return strdup(result.c_str());
}

//------------------------------------------------

const char *cmp_intg(const long long, const char,
                     const long long);
const char *cmp_flot(const double, const char,
                     const double);
const char *cmp_char(const char, const char,
                     const char);
const char *cmp_strg(const char *const, const char,
                     const char *const);
const char *cmp_bool(const char *const, const char,
                     const char *const);

char *cmp_vals(const char *const v0, const char op,
               const char *const v1)
{
  if (nullptr == v0 || nullptr == v1 ||
      false == is_valid(v0) || false == is_valid(v1))
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

  // success
  if (0 == strcmp(frst_type.c_str(), INTG_DATA_TYPE))
    return strdup(cmp_intg(atoll(v0), op, atoll(v1)));
  else if (0 == strcmp(frst_type.c_str(), FLOT_DATA_TYPE))
    return strdup(cmp_flot(atof(v0), op, atof(v1)));
  else if (0 == strcmp(frst_type.c_str(), CHAR_DATA_TYPE))
    return strdup(cmp_char(*v0, op, *v1));
  else if (0 == strcmp(frst_type.c_str(), STRG_DATA_TYPE))
    return strdup(cmp_strg(v0, op, v1));

  const char *ptr = cmp_bool(v0, op, v1);
  if (ptr)
    return strdup(ptr);
  yyerror("cmp_vals() failed - "
          "bool can not be compared like that");
  return nullptr;
}

const char *cmp_intg(const long long v0, const char op,
                     const long long v1)
{
  if (EE_CHR == op)
    return v0 == v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (NE_CHR == op)
    return v0 != v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (LE_CHR == op)
    return v0 <= v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (LS_CHR == op)
    return v0 < v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (GE_CHR == op)
    return v0 >= v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (GS_CHR == op)
    return v0 > v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else
    return nullptr;
}

const char *cmp_flot(const double v0, const char op,
                     const double v1)
{
  if (EE_CHR == op)
    return v0 == v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (NE_CHR == op)
    return v0 != v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (LE_CHR == op)
    return v0 <= v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (LS_CHR == op)
    return v0 < v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (GE_CHR == op)
    return v0 >= v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (GS_CHR == op)
    return v0 > v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else
    return nullptr;
}

const char *cmp_char(const char v0, const char op,
                     const char v1)
{
  if (EE_CHR == op)
    return v0 == v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (NE_CHR == op)
    return v0 != v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (LE_CHR == op)
    return v0 <= v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (LS_CHR == op)
    return v0 < v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (GE_CHR == op)
    return v0 >= v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (GS_CHR == op)
    return v0 > v1 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else
    return nullptr;
}

const char *cmp_strg(const char *const v0, const char op,
                     const char *const v1)
{
  const int result = strcmp(v0, v1);
  if (EE_CHR == op)
    return result == 0 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (NE_CHR == op)
    return result != 0 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (LE_CHR == op)
    return result <= 0 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (LS_CHR == op)
    return result < 0 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (GE_CHR == op)
    return result >= 0 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (GS_CHR == op)
    return result > 0 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else
    return nullptr;
}

const char *cmp_bool(const char *const v0, const char op,
                     const char *const v1)
{
  const int result = strcmp(v0, v1);
  if (EE_CHR == op)
    return result == 0 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  else if (NE_CHR == op)
    return result != 0 ? BOOL_LITERAL_1 : BOOL_LITERAL_0;
  return nullptr;
}

#endif
