#ifndef __0DEFINITION0__
#define __0DEFINITION0__

/* comments:
 * nullptr => error occured
 * item_data memory removal is performed by tables
 * and not here
 */

#include <vector>
#include "class/dev/ast.hpp"
#include "class/dev/yyerror.hpp"
#include "class/dev/item_data.hpp"

#include "class/class_data.hpp"
#include "class/symbol_table.hpp"
#include "class/type_table.hpp"
#include "ast_call.hpp"

extern std::vector<symbol_table> symbols;
#define LAST_SCOPE symbols.size() - 1

class ast_typecall : public ast_statement
{
  char *const id;
  class_data *const data;

public:
  virtual ~ast_typecall() override;
  ast_typecall(char *const,
               class_data *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_typecall::~ast_typecall()
{
  free(id);
  // last reminder about item_data's memory
  // delete data;
}

ast_typecall::ast_typecall(
    char *const id,
    class_data *const data)
    : id(id), data(data)
{
  if (nullptr == id || nullptr == data)
    yyerror("ast_typecall() failed - received nullptr");

  if (0 != LAST_SCOPE)
    yyerror("ast_typecall() failed - class declared in scope");
}

void *ast_typecall::evaluate()
{
  if (type_exists(id) || scope_search(id))
  {
    yyerror("ast_typecall() failed - id already defined");
    return nullptr;
  }

  type_insert(id, data);
  return data;
}

const char ast_typecall::get_stat_type() const
{
  return TYC_STAT_TYPE;
}

class ast_definiton : public ast_statement
{
  char *const data_type;
  char *const id;
  ast_expression *const value;

public:
  virtual ~ast_definiton() override;
  ast_definiton(char *const, char *const,
                ast_expression *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_definiton::~ast_definiton()
{
  free(data_type);
  free(id);
  delete value;
}

ast_definiton::ast_definiton(
    char *const type, char *const id,
    ast_expression *const value)
    : data_type(type), id(id), value(value)
{
  if (nullptr == type || nullptr == id ||
      nullptr == value)
    yyerror("ast_definiton() failed - received nullptr");
}

void *ast_definiton::evaluate()
{
  if (is_type(id))
  {
    yyerror("ast_definiton() failed - already defined id");
    return nullptr;
  }

  if (scope_search(id))
  {
    yyerror("ast_definiton() failed - already defined id");
    return nullptr;
  }

  // void *buffer =
  // symbols[LAST_SCOPE].insert(id, data);
  // return data;
  return nullptr;
}

const char ast_definiton::get_stat_type() const
{
  return DEF_STAT_TYPE;
}

class ast_declaration : public ast_statement
{
  char *const data_type;
  char *const id;

public:
  virtual ~ast_declaration() override;
  ast_declaration(char *const, char *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_declaration::~ast_declaration()
{
  free(data_type);
  free(id);
}

ast_declaration::ast_declaration(
    char *const type, char *const id)
    : data_type(type), id(id)
{
  if (nullptr == type || nullptr == id)
    yyerror("ast_declaration() failed - received nullptr");
}

void *ast_declaration::evaluate()
{
  if (is_type(id))
  {
    yyerror("ast_declaration() failed - already defined id");
    return nullptr;
  }

  if (scope_search(id))
  {
    yyerror("ast_declaration() failed - already defined id");
    return nullptr;
  }

  // todo create data based on data_type
  return id;
}

const char ast_declaration::get_stat_type() const
{
  return DCL_STAT_TYPE;
}

#endif
