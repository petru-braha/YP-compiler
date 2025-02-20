#ifndef __0UTILITY0__
#define __0UTILITY0__

#include "class/dev/ast.hpp"
#include "class/dev/yyerror.hpp"
#include "class/dev/symbol_data.hpp"
#include "class/dev/function.hpp"

#include "class/primitive_data.hpp"
#include "class/function_data.hpp"
#include "class/object_data.hpp"
#include "class/array_data.hpp"
#include "class/class_data.hpp"

#include "class/symbol_table.hpp"
#include "class/scope_stack.hpp"
#include "class/type_table.hpp"

// the place of all global variables
extern FILE *yyin;
extern char *yytext;
extern int yylineno;
size_t count_error;

void yywarning(const char *message)
{
  count_error++;
  printf("%s warning - line %d: %s.\n",
         __FILE__, yylineno, message);
}

// stops my compiler
void yyerror(const char *message)
{
  count_error++;
  printf("%s error - line %d: %s.\n",
         __FILE__, yylineno, message);
  if (0 == strcmp(message, "syntax error"))
    printf("the program has %zu errors.\n", count_error);
}

bool is_primitive(const std::string &type)
{
  for (unsigned char i = 0; i < COUNT_RESERVED_TYPES; i++)
    if (std::string(RESERVED_TYPES[i]) == type)
      return true;
  return false;
}

// should be used only for primitive types
std::string default_value_of(const std::string &type)
{
  if (std::string(INTG_DATA_TYPE) == type)
    return "0";
  if (std::string(FLOT_DATA_TYPE) == type)
    return "0.0";
  if (std::string(CHAR_DATA_TYPE) == type)
    return "\'0\'";
  if (std::string(STRG_DATA_TYPE) == type)
    return "\"\"";
  if (std::string(BOOL_DATA_TYPE) == type)
    return "false";

  // not primitive
  return "";
}

std::string type_of(const std::string &primitive_value)
{
  switch (primitive_value.at(0))
  {
  default:
    if (primitive_value.find('.') == std::string::npos)
      return INTG_DATA_TYPE;
    return FLOT_DATA_TYPE;
  case '\'':
    return CHAR_DATA_TYPE;
  case '\"':
    return STRG_DATA_TYPE;
  case 't':
    return BOOL_DATA_TYPE;
  case 'f':
    return BOOL_DATA_TYPE;
  }
}

bool make_copy(mutable_data *&left, const symbol_data *const rght)
{
  if (nullptr == rght)
    return false;
  if (left && FNCT_SYMB_TYPE == left->get_item_type())
    return false;
  if (FNCT_SYMB_TYPE == rght->get_item_type())
    return false;

  if (PRMT_SYMB_TYPE == rght->get_item_type())
  {
    primitive_data *p_data = (primitive_data *)rght;
    left = new primitive_data(p_data->get_data_type(), *p_data);
  }

  if (OBJT_SYMB_TYPE == rght->get_item_type())
  {
    object_data *o_data = (object_data *)rght;
    left = new object_data(o_data->get_data_type(), *o_data);
  }

  if (ARRY_SYMB_TYPE == rght->get_item_type())
  {
    array_data *a_data = (array_data *)rght;
    left = new array_data(a_data->get_data_type(), *a_data);
  }

  return true;
}

bool is_type(const std::string &data_type)
{
  std::string base = base_type(data_type);
  if ("" != base)
    return is_primitive(base) || type_exists(base);
  return is_primitive(data_type) || type_exists(data_type);
}

/* a constant value can only be primitive */
bool is_compatible(const char *type, const char *constant_value)
{
  switch (constant_value[0])
  {
  default: // int
    if (nullptr == strchr(constant_value, '.'))
    {
      if (0 != strcmp(type, INTG_DATA_TYPE))
        return false;
    }
    else
    {
      // float
      if (0 != strcmp(type, FLOT_DATA_TYPE))
        return false;
    }
    break;

  case '\'': // char
    if (strcmp(type, CHAR_DATA_TYPE))
      return false;
    break;

  case 't': // bool
    if (strcmp(type, BOOL_DATA_TYPE))
      return false;
    break;
  case 'f': // bool
    if (strcmp(type, BOOL_DATA_TYPE))
      return false;
    break;

  case '\"': // string
    if (strcmp(type, STRG_DATA_TYPE))
      return false;
    break;
  }

  return true;
}

// bool is_returning_defn(ast_statement *const node);
bool is_returning_char(ast_expression *const node)
{
  if (nullptr == node)
    return false;

  if (node->get_stat_type() == CST_STAT_TYPE ||
      node->get_stat_type() == OPR_STAT_TYPE ||
      node->get_stat_type() == MTS_STAT_TYPE)
    return true;
  return false;
}

/* expression of primitive_data
 * also evaluates the expression
 * provides error messages
 */
const char *get_buffer(ast_expression *const node)
{
  if (nullptr == node)
  {
    yyerror("get_buffer() failed - received nullptr");
    return nullptr;
  }

  void *buffer = node->evaluate();
  if (is_returning_char(node))
    return (char *)buffer;

  symbol_data *data = (symbol_data *)buffer;
  if (PRMT_SYMB_TYPE != data->get_item_type() ||
      false == is_primitive(data->get_data_type()))
  {
    yyerror("get_buffer() failed - not primitive type");
    return nullptr;
  }

  primitive_data *p = (primitive_data *)data;
  return p->get_value().c_str();
}

/*
 * type_of(std::string); - high-level call
 * type_of(const char *); - vanilla call
 */
void *type_of(const char *const buffer, const char)
{
  std::string type = type_of(std::string(buffer));
  char *data = (char *)malloc(type.size());
  strcpy(data, type.c_str());

  data[type.size() - 1] = '\0';
  return data;
}

bool is_lawful(const char *const string_literal)
{
  if (nullptr == string_literal || '\"' != *string_literal)
    return false;
  if ('\0' == string_literal[1])
    return false;

  // if an escape sequence was previously detected
  bool prev_escape = false;
  constexpr char seq[] = "abfnrtv\\'\"0";

  for (size_t i = 1;
       '\"' != string_literal[i] ||
       '\0' != string_literal[i + 1];
       i++)
  {
    char c = string_literal[i];
    if (prev_escape)
    {
      if (nullptr == strchr(seq, c))
        return false;
      prev_escape = false;
      continue;
    }

    // false == prev_escape
    if ('\'' == c || '\"' == c)
      return false;
    if ('\\' == c)
      prev_escape = true;
  }

  if (prev_escape)
    return false;
  return true;
}

// it is assured by flex that the string is valid
bool interpret(const char character)
{
  switch (character)
  {
  case 'a':
    printf("\a");
    break;
  case 'b':
    printf("\b");
    break;
  case 'f':
    printf("\f");
    break;
  case 'n':
    printf("\n");
    break;
  case 'r':
    printf("\r");
    break;
  case 't':
    printf("\t");
    break;
  case 'v':
    printf("\v");
    break;
  case '\\':
    printf("\\");
    break;
  case '\'':
    printf("\'");
    break;
  case '\"':
    printf("\"");
    break;
  case '0':
    return true;
  default:
    printf("-stop-error");
    return true;
  }

  return false;
}

// it is assured by flex that the string is valid
size_t print_f_string(const char *literal)
{
  if (nullptr == literal || '\"' != *literal)
    return -1;
  if ('\0' == literal[1])
    return -1;

  // if an escape sequence was previously detected
  bool prev_escape = false;
  size_t bytes = 0;
  constexpr char seq[] = "abfnrtv\\'\"0";

  for (size_t i = 1;
       '\"' != literal[i] ||
       '\0' != literal[i + 1];
       i++)
  {
    char c = literal[i];
    if (prev_escape)
    {
      if (nullptr == strchr(seq, c))
        return -1;
      if (interpret(c))
        return bytes;
      bytes++;
      prev_escape = false;
      continue;
    }

    // false == prev_escape
    if ('\'' == c || '\"' == c)
      return -1;
    if (literal[i] != '\\')
      bytes += printf("%c", literal[i]);
    else
      prev_escape = true;
  }

  if (prev_escape)
    return -1;
  return bytes;
}

void *print_f(const char *const buffer, const char)
{
  size_t n = 0;
  if (buffer[0] != '\"')
    n = printf("%s", buffer);
  else
    n = print_f_string(buffer);

  if (-1 == n)
    return nullptr;
  char *data = strdup(std::to_string(n).c_str());
  return data;
}

void initialize_compiler()
{
  if (scope_stack::size())
    return;

  symbol_insert(
      "type_of",
      new function_data(
          STRG_DATA_TYPE,
          new function_data::map(),
          new std::vector<ast_statement *>()));

  symbol_insert(
      "print_f",
      new function_data(
          INTG_DATA_TYPE,
          new function_data::map(),
          new std::vector<ast_statement *>()));

  symbol_insert(
      "master",
      new function_data(
          INTG_DATA_TYPE,
          new function_data::map(),
          new std::vector<ast_statement *>()));
}

#endif
