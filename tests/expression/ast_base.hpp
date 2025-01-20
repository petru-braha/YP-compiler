#ifndef __0ASTNODE0__
#define __0ASTNODE0__

#include "util.hpp"

class ast_node
{
public:
  virtual ~ast_node() = default;
  virtual const char *evaluate() = 0;
};

/* its type is predefined
 * leaf nodes
 * store a value
 */
class ast_variable final : public ast_node
{
  std::string value;

public:
  ast_variable(const char *const v) : value(v)
  {
    if (nullptr == v)
      yyerror("ast_variable() failed - received nullptr");
  }

  const char *evaluate() override
  {
    return value.c_str();
  }
};

std::string plus(const char *, const *)

/* its type is predefined
 * and determined by its children nodes
 * unary opearators are encoded here too (!, -)
 * store an operation
 */
class ast_operation final : public ast_node
{
  ast_node *left_child;
  ast_node *rght_child;
  std::string operation;

public:
  ast_operation(ast_node *const o0,
                const char *const op,
                ast_node *const o1)
      : left_child(o0), operation(op), rght_child(o1)
  {
    if (nullptr == op)
    {
      yyerror("ast_operation() failed - received nullptr");
      return;
    }

    // unary operator
    if (1 == operation.size() &&
        ('!' == op[0] || '-' == op[0]))
    {
      if (nullptr != o0)
        yyerror("unary operators expect one argument");
      return;
    }

    // binary operator
    if (nullptr == o0 || nullptr == o1)
      yyerror("binary operators expect two arguments");
  }

  const char *evaluate() override
  {
    switch (operation.at(0))
    {

    // check if left_child is nullptr
    case '!':
      break;
    case '-':
      break;

    case '+':
      return left_child->evaluate(), rght_child->evaluate();
      break;
    case '&':
      break;
    case '|':
      break;

    case '*':
      break;
    case '/':
      break;
    case '%':
      break;

    case '^':

    // check for the second character
    case '=':
    case '<':
    case '>':

    // error
    default:
      break;
    }
  }
};

// maybe implement a recursive deconstructor

#endif