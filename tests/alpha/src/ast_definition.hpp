#ifndef __0DEFINITION0__
#define __0DEFINITION0__

/* comments:
 * nullptr => error occured
 * item_data memory removal is performed by tables
 * and not here
 */

#include <vector>
#include "class/dev/yyerror.hpp"
#include "class/dev/item_data.hpp"
#include "class/dev/ast.hpp"

#include "class/class_data.hpp"
#include "class/symbol_table.hpp"
#include "class/type_table.hpp"

extern std::vector<symbol_table> symbols;
#define LAST_SCOPE symbols.size() - 1

class ast_typecall : public ast_statement
{
  const char *const id;
  class_data *const data;

public:
  virtual ~ast_typecall() override;
  ast_typecall(const char *const,
               class_data *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_typecall::~ast_typecall()
{
  delete id;
  // last reminder about item_data's memory
  // delete data;
}

ast_typecall::ast_typecall(
    const char *const id,
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
  const char *const id;
  item_data *const data;

public:
  virtual ~ast_definiton() override;
  ast_definiton(const char *const,
                item_data *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_definiton::~ast_definiton()
{
  delete id;
}

ast_definiton::ast_definiton(
    const char *const id, item_data *const data)
    : id(id), data(data)
{
  if (nullptr == id || nullptr == data)
    yyerror("ast_definiton() failed - received nullptr");
}

void *ast_definiton::evaluate()
{
  if (is_type(id))
  {
    yyerror("ast_definiton() failed - received nullptr");
    return nullptr;
  }

  if (scope_search(id))
  {
    yyerror("ast_definiton() failed - received nullptr");
    return nullptr;
  }

  symbols[LAST_SCOPE].insert(id, data);
  return data;
}

const char ast_definiton::get_stat_type() const
{
  return DEF_STAT_TYPE;
}


#endif
