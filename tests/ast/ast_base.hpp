#ifndef __0ASTNODE0__
#define __0ASTNODE0__

#include <vector>
#include "arithmetic.hpp"

class item_data;

class ast_statement
{
public:
  virtual ~ast_statement() = default;
  virtual char *evaluate() const = 0;
};

class ast_expression : public ast_statement
{
public:
  virtual ~ast_expression() = default;
};

/* its type is predefined
 * leaf nodes
 * store a value
 */
class ast_variable final : public ast_expression
{
  char *value;

public:
  ~ast_variable();
  ast_variable(const char *const v);

  char *evaluate() const override;
};

ast_variable::~ast_variable()
{
  delete value;  
}

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
  const ast_expression *const left_child;
  const ast_expression *const rght_child;
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
    result = asg_vals(v0, v1);
  else
    result = cmp_vals(v0, operation, v1);

  //todo free?
  return result;
}

//------------------------------------------------

// todo should add const?
class ast_scope : public ast_statement
{
  std::vector<ast_statement *> statemets;

public:
  ~ast_scope();
  ast_scope(const std::vector<ast_statement *> *const);

  char *evaluate() const override;
};

ast_scope::~ast_scope()
{
  for (size_t i = 0; i < statemets.size(); i++)
    delete statemets[i];
}

ast_scope::ast_scope(const std::vector<ast_statement *> *const s)
{
  if (nullptr == s)
    return;

  for (size_t i = 0; i < statemets.size(); i++)
    if (nullptr == statemets[i])
    {
      yyerror("ast_scope() failed - received nullptr");
      return;
    }
}

char *ast_scope::evaluate() const
{
  printf("%d\n", statemets.size());
  for (size_t i = 0; i < statemets.size(); i++)
    statemets[i]->evaluate();
  return nullptr;
}

class ast_ifelse : public ast_statement
{
  const ast_expression *const judge;
  const ast_statement *const sucss_case;
  const ast_statement *const failr_case;

public:
  ~ast_ifelse();
  ast_ifelse(const ast_expression *const,
             const ast_statement *const,
             const ast_statement *const);

  char *evaluate() const override;
};

ast_ifelse::~ast_ifelse()
{
  delete judge;
  delete sucss_case;
  delete failr_case;
}

ast_ifelse::ast_ifelse(const ast_expression *const j,
                       const ast_statement *const s,
                       const ast_statement *const f)
    : judge(j), sucss_case(s), failr_case(f)
{
  if (nullptr == judge || nullptr == sucss_case)
    yyerror("ast_ifelse() failed - received nullptr");
}

char *ast_ifelse::evaluate() const
{
  if (0 == strcmp("true", judge->evaluate()))
    return sucss_case->evaluate();
  return failr_case->evaluate();
}

class ast_while : public ast_statement
{
  const ast_expression *const judge;
  const ast_statement *const sucss_case;

public:
  ~ast_while();
  ast_while(const ast_expression *const,
            const ast_statement *const);

  char *evaluate() const override;
};

ast_while::~ast_while()
{
  delete judge;
  delete sucss_case;
}

ast_while::ast_while(const ast_expression *const j,
                     const ast_statement *const s)
    : judge(j), sucss_case(s)
{
  if (nullptr == judge || nullptr == sucss_case)
    yyerror("ast_while() failed - received nullptr");
}

char *ast_while::evaluate() const
{
  while (0 == strcmp("true", judge->evaluate()))
    sucss_case->evaluate();
  return nullptr;
}

class ast_for : public ast_statement
{
  const ast_expression *const initl;
  const ast_expression *const judge;
  const ast_expression *const incrm;
  const ast_statement *const sucss_case;

public:
  ~ast_for();
  ast_for(const ast_expression *const,
          const ast_expression *const,
          const ast_expression *const,
          const ast_statement *const);

  char *evaluate() const override;
};

ast_for::~ast_for()
{
  delete initl;
  delete judge;
  delete incrm;
  delete sucss_case;
}

ast_for::ast_for(const ast_expression *const iti,
                 const ast_expression *const jdj,
                 const ast_expression *const inc,
                 const ast_statement *const s)
    : initl(iti), judge(jdj), incrm(inc), sucss_case(s)
{
  if (nullptr == judge || nullptr == sucss_case)
    yyerror("ast_for() failed - received nullptr");
}

char *ast_for::evaluate() const
{
  for (initl ? initl->evaluate() : 0;
       judge ? judge->evaluate() : 0;
       incrm ? incrm->evaluate() : 0)
  {
    sucss_case->evaluate();
    printf("iteration\n");
  }
  return nullptr;
}

#endif