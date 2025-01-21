#ifndef __0ASTNODE0__
#define __0ASTNODE0__

#include "arithmetic.hpp"

class ast_node
{
public:
  virtual ~ast_node() = default;
  virtual char *evaluate() = 0;
};

/* its type is predefined
 * leaf nodes
 * store a value
 */
class ast_variable final : public ast_node
{
  char *value;

public:
  ~ast_variable() = default;
  ast_variable(const char *const v);

  char *evaluate() override;
};

ast_variable::ast_variable(const char *const v)
    : value(strdup(v))
{
  if (nullptr == v)
    yyerror("ast_variable() failed - received nullptr");
}

char *ast_variable::evaluate()
{
  return value;
}

/* its type is predefined
 * and determined by its children nodes
 * unary opearators are encoded here too (!, -)
 * store an operation
 */
class ast_operation final : public ast_node
{
  ast_node *left_child;
  ast_node *rght_child;
  const char operation;

public:
  ~ast_operation();
  ast_operation(ast_node *const, const char,
                ast_node *const);

  char *evaluate() override;
};

// recursive deconstructor
ast_operation::~ast_operation()
{
  delete left_child;
  delete rght_child;
}

ast_operation::ast_operation(ast_node *const o0, const char op,
                             ast_node *const o1)
    : left_child(o0), rght_child(o1), operation(op)
{
  if (nullptr == o0 || nullptr == o1)
    yyerror("ast_operation() failed - received nullptr");
}

char *ast_operation::evaluate()
{
  char *result = nullptr;
  char *v0 = left_child->evaluate();
  char *v1 = rght_child->evaluate();

  if ('+' == operation)
    result = add_vals(v0, v1);
  else if ('-' == operation)
    result = sub_vals(v0, v1);
  else if ('&' == operation)
    result = and_vals(v0, v1);
  else if ('|' == operation)
    result = or__vals(v0, v1);
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

  free((void *)v0);
  free((void *)v1);
  return result;
}

#endif