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
#include "class/type_table.hpp"

// the place of all global variables
extern FILE *yyin;
extern char *yytext;
extern int yylineno;
size_t count_error;
char yyaccess;
std::vector<symbol_table> symbols;
#define LAST_SCOPE symbols.size() - 1

void yywarning(const char *message)
{
  count_error++;
  printf("%s warning - line %d: %s.\n",
         __FILE__, yylineno, message);
}

// breaks
void yyerror(const char *message)
{
  count_error++;
  printf("%s error - line %d: %s.\n",
         __FILE__, yylineno, message);
  if (0 == strcmp(message, "syntax error"))
    printf("the program has %zu errors.\n", count_error);
}

mutable_data *make_copy(const mutable_data *const data)
{
  if (nullptr == data)
    return nullptr;

  if (PRMT_SYMB_TYPE == data->get_item_type())
  {
    primitive_data *p_data = (primitive_data *)data;
    return new primitive_data(p_data->get_data_type(), *p_data);
  }

  if (OBJT_SYMB_TYPE == data->get_item_type())
  {
    object_data *o_data = (object_data *)data;
    return new object_data(o_data->get_data_type(), *o_data);
  }

  if (ARRY_SYMB_TYPE == data->get_item_type())
  {
    array_data *a_data = (array_data *)data;
    return new array_data(a_data->get_data_type(), *a_data);
  }

  return nullptr;
}

/* goes through every scope
 * could add extra time complexity
 */
symbol_data *scope_search(const std::string &id)
{
  if (0 == symbols.size())
    return nullptr;

  for (size_t scope = LAST_SCOPE;; scope--)
  {
    symbol_data *data = symbols[scope].get_data(id);
    if (data)
      return data;
    if (0 == scope)
      break;
  }

  return nullptr;
}

bool is_type(const std::string &id)
{
  return type_exists(id) || is_primitive(id);
}

/* a constant value can only be primitive */
bool is_compatible(const char *type, const char *constant_value)
{
  switch (constant_value[0])
  {
  default: // int
    if (nullptr == strchr(constant_value, '.'))
      if (strcmp(type, INTG_DATA_TYPE))
        return false;

    // float
    if (strcmp(type, FLOT_DATA_TYPE))
      return false;
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

void *print_f(const char *const buffer, const char)
{
  int number = printf("%s", buffer);
  char *data = strdup(std::to_string(number).c_str());
  return data;
}

void initialize_compiler()
{
  symbols.emplace_back();
  symbol_table &s = symbols[LAST_SCOPE];

  s.insert(
      "type_of",
      new function_data(
          STRG_DATA_TYPE,
          new std::unordered_map<
              std::string, mutable_data *>(),
          new std::vector<ast_statement *>()));

  s.insert(
      "print_f",
      new function_data(
          INTG_DATA_TYPE,
          new std::unordered_map<
              std::string, mutable_data *>(),
          new std::vector<ast_statement *>()));

  s.insert(
      "master",
      new function_data(
          INTG_DATA_TYPE,
          new std::unordered_map<
              std::string, mutable_data *>(),
          new std::vector<ast_statement *>()));
}

#endif
