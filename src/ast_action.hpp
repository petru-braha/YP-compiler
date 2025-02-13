#ifndef __0ACTION0__
#define __0ACTION0__

/* comments:
 * nullptr => error occured
 * item_data memory removal is performed by tables
 * and not here
 */

#include <vector>
#include "class/dev/ast.hpp"
#include "class/dev/yyerror.hpp"
#include "class/dev/item_data.hpp"

#include "class/symbol_table.hpp"

extern std::vector<symbol_table> symbols;
#define LAST_SCOPE symbols.size() - 1

constexpr char ACT_BREAK = 124;
constexpr char ACT_CONTINUE = 125;
constexpr char ACT_RETURN = 126;

class ast_action : public ast_statement
{
  const char action;

public:
  virtual ~ast_action() override = default;
  ast_action(const char);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_action::ast_action(const char act)
    : action(act)
{
}

void *ast_action::evaluate()
{
  return (void *)&action;
}

const char ast_action::get_stat_type() const
{
  return ACT_STAT_TYPE;
}

struct return_value
{
  const char action = ACT_RETURN;
  mutable_data *value;
};

class ast_return : public ast_statement
{
  ast_expression *const data;
  return_value result;

public:
  virtual ~ast_return() override;
  ast_return(ast_expression *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_return::~ast_return()
{
  delete data;
}

ast_return::ast_return(ast_expression *const e)
    : data(e), result({ACT_RETURN, nullptr})
{
  if (nullptr == e)
    yyerror("ast_return() failed - received nullptr");
}

void *ast_return::evaluate()
{
  void *buffer = data->evaluate();
  if (is_returning_char(data))
  {
    char *value = (char *)buffer;
    result.value = new primitive_data(
        type_of(value), value);
    return (void *)&result;
  }

  item_data *temp = (item_data *)buffer;
  if (FNCT_ITEM_TYPE == temp->get_item_type())
  {
    yyerror("ast_return() failed - received function");
    return nullptr;
  }

  result.value = (mutable_data *)temp;
  return (void *)&result;
}

const char ast_return::get_stat_type() const
{
  return RET_STAT_TYPE;
}

#endif
