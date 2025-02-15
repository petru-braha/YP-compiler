#ifndef __0EXPRESSION0__
#define __0EXPRESSION0__

/* comments:
 * nullptr => error occured
 * symbol_data memory removal is performed by tables
 * and not here
 */

#include "class/dev/ast.hpp"
#include "class/dev/yyerror.hpp"
#include "class/dev/symbol_data.hpp"
#include "class/dev/ast_alphabet.hpp"
#include "class/dev/ast_arithmetic.hpp"

#include "ast_call.hpp"

/* primitive data type
 * stored as leaf nodes
 * used for literals
 */
class ast_constant : public ast_expression
{
  char *value;

public:
  virtual ~ast_constant() override;
  ast_constant(char *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_constant::~ast_constant()
{
  free(value);
}

ast_constant::ast_constant(char *const v)
    : value(v)
{
  if (nullptr == v)
    yyerror("ast_constant() failed - received nullptr");
}

void *ast_constant::evaluate()
{
  return value;
}

const char ast_constant::get_stat_type() const
{
  return CST_STAT_TYPE;
}

/* primitive data type
 * unary opearators are encoded here too (!, -)
 * store an operation
 */
class ast_operator : public ast_expression
{
  char *result;
  ast_expression *const left_child;
  ast_expression *const rght_child;
  const char operation;

public:
  virtual ~ast_operator() override;
  ast_operator(ast_expression *const, const char,
               ast_expression *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

// recursive deconstructor
ast_operator::~ast_operator()
{
  free(result);
  delete left_child;
  delete rght_child;
}

ast_operator::ast_operator(
    ast_expression *const o0, const char op,
    ast_expression *const o1)
    : result(nullptr),
      left_child(o0), rght_child(o1), operation(op)
{
  if (ASG_CHR == op)
    yyerror("ast_operator() failed - use ast_assign() instead");
  if (nullptr == o0 || nullptr == o1)
    yyerror("ast_operator() failed - received nullptr");
}

void *ast_operator::evaluate()
{
  const char *v0 = get_buffer(left_child);
  const char *v1 = get_buffer(rght_child);

  // unary
  if ('!' == operation && nullptr == v0)
    result = negation(v1);
  else if ('-' == operation && nullptr == v0)
    result = chg_sign(v1);

  // binary - no assignation
  else if ('+' == operation)
    result = add_vals(v0, v1);
  else if ('-' == operation)
    result = sub_vals(v0, v1);
  else if ('&' == operation)
    result = and_vals(v0, v1);
  else if ('|' == operation)
    result = or__vals(v0, v1);
  else if (XOR_CHR == operation)
    result = xor_vals(v0, v1);
  else if ('*' == operation)
    result = mul_vals(v0, v1);
  else if ('/' == operation)
    result = div_vals(v0, v1);
  else if ('%' == operation)
    result = mod_vals(v0, v1);
  else if ('^' == operation)
    result = pow_vals(v0, v1);
  else
    result = cmp_vals(v0, operation, v1);

  return result;
}

const char ast_operator::get_stat_type() const
{
  return OPR_STAT_TYPE;
}

// here, left_child is evaluated last
class ast_assign : public ast_expression
{
  ast_symbolcall *const left_child;
  ast_expression *const rght_child;

public:
  virtual ~ast_assign() override;
  ast_assign(ast_symbolcall *const,
             ast_expression *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_assign::~ast_assign()
{
  delete rght_child;
  delete left_child;
}

ast_assign::ast_assign(
    ast_symbolcall *const v0,
    ast_expression *const v1)
    : left_child(v0), rght_child(v1)
{
  if (nullptr == v0 || nullptr == v1)
    yyerror("ast_assign() failed - received nullptr");
}

// returns mutable_data*
void *ast_assign::evaluate()
{
  symbol_data *left = (symbol_data *)left_child->evaluate();
  if (FNCT_SYMB_TYPE == left->get_item_type())
  {
    yyerror("ast_assign() failed - received function symbol");
    return nullptr;
  }

  mutable_data *data = nullptr;
  void *rght = rght_child->evaluate();

  if (is_returning_char(rght_child))
  {
    char *value = (char *)rght;
    data = new primitive_data(type_of(value), value);

    if (data->get_item_type() != left->get_item_type() ||
        data->get_data_type() != left->get_data_type())
    {
      yyerror("ast_assign() failed - type missmatch");
      return nullptr;
    }

    delete left;
    left = data;
    return left;
  }

  // is_returning_char == false
  symbol_data *temp = (symbol_data *)rght;
  if (FNCT_SYMB_TYPE == temp->get_item_type())
  {
    yyerror("ast_assign() failed - received function symbol");
    return nullptr;
  }
  data = (mutable_data *)temp;

  if (data->get_item_type() != left->get_item_type() ||
      data->get_data_type() != left->get_data_type())
  {
    yyerror("ast_assign() failed - type missmatch");
    return nullptr;
  }

  delete left;
  left = make_copy(data);
  return left;
}

const char ast_assign::get_stat_type() const
{
  return ASG_STAT_TYPE;
}

#endif
