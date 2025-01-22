#ifndef __0ASTNODE0__
#define __0ASTNODE0__

#include <vector>
#include "arithmetic.hpp"

class item_data;
class ast_expression;

class ast_statement
{
public:
  virtual ~ast_statement() = default;
  virtual char *evaluate() const = 0;
};

class ast_scope : public ast_statement
{
  std::vector<ast_statement *> statemets;

public:
  ~ast_scope();
  ast_scope();

  ast_scope &add(const ast_statement *const);
  char *evaluate() const override;
};

class ast_ifelse : public ast_statement
{
  ast_expression *judge;
  ast_scope *sucss_case;
  ast_scope *failr_case;

public:
  ~ast_ifelse();
  ast_ifelse();

  char *evaluate() const override;
};

class ast_while : public ast_statement
{
  ast_expression *judge;
  ast_scope *sucss_case;

public:
  ~ast_while();
  ast_while();

  char *evaluate() const override;
};

class ast_for : public ast_statement
{
  ast_expression *initl;
  ast_expression *judge;
  ast_expression *incrm;
  ast_scope *sucss_case;

public:
  ~ast_for();
  ast_for();

  char *evaluate() const override;
};

//------------------------------------------------

class ast_expression : public ast_statement
{
};

/* its type is predefined
 * leaf nodes
 * store a value
 */
class ast_variable final : public ast_expression
{
  char *value;

public:
  ~ast_variable() = default;
  ast_variable(const char *const v);

  char *evaluate() const override;
};

ast_variable::ast_variable(const char *const v)
    : value(strdup(v))
{
  if (nullptr == v)
    yyerror("ast_variable() failed - received nullptr");
}

char *ast_variable::evaluate() const
{
  return value;
}

/* its type is predefined
 * and determined by its children nodes
 * unary opearators are encoded here too (!, -)
 * store an operation
 * assignation
 */
class ast_operator final : public ast_expression
{
  ast_expression *left_child;
  ast_expression *rght_child;
  const char operation;

public:
  ~ast_operator();
  ast_operator(ast_expression *const, const char,
               ast_expression *const);

  char *evaluate() const override;
};

// recursive deconstructor
ast_operator::~ast_operator()
{
  delete left_child;
  delete rght_child;
}

ast_operator::ast_operator(ast_expression *const o0, const char op,
                           ast_expression *const o1)
    : left_child(o0), rght_child(o1), operation(op)
{
  if ((nullptr == o0 && '!' != op && '-' != op) ||
      nullptr == o1)
    yyerror("ast_operator() failed - received nullptr");
}

char *ast_operator::evaluate() const
{
  char *result = nullptr;
  char *v0 = left_child ? left_child->evaluate() : nullptr;
  char *v1 = rght_child->evaluate();

  // unary
  if ('!' == operation && nullptr == v0)
    result = negation(v1);
  else if ('-' == operation && nullptr == v0)
    result = chg_sign(v1);

  // binary
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
  else if (ASG_CHR == operation)
  {
    // todo
  }
  else
    result = cmp_vals(v0, operation, v1);

  free((void *)v0);
  free((void *)v1);
  return result;
}

#endif