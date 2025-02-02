#ifndef __0ASTNODE0__
#define __0ASTNODE0__

#include <vector>
#include "class/dev/alphabet.hpp"
#include "arithmetic.hpp"
#include "data.hpp"

std::vector<symbol_table> symbols;
#define LAST_SCOPE symbols.size() - 1

constexpr char VAR_STAT_TYPE = 100;
constexpr char OPR_STAT_TYPE = 101;
constexpr char ASG_STAT_TYPE = 102;
constexpr char SCP_STAT_TYPE = 103;
constexpr char IFE_STAT_TYPE = 104;
constexpr char WHL_STAT_TYPE = 105;
constexpr char FOR_STAT_TYPE = 106;
constexpr char DEF_STAT_TYPE = 107;

class ast_statement
{
public:
  virtual ~ast_statement() = default;
  virtual const char get_type() const = 0;
  virtual char *evaluate() const = 0;
};

class ast_expression : public ast_statement
{
public:
  virtual ~ast_expression() = default;
};

/* its type is predefined
 * leaf nodes
 * store a value of a reserved type
 */
class ast_variable final : public ast_expression
{
  char *value;

public:
  ~ast_variable();
  ast_variable(const char *const v);
  ast_variable(const item_data *const);

  const char get_type() const override;
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

ast_variable::ast_variable(const item_data *const data)
{
  if (nullptr == data)
    yyerror("ast_variable() failed - undefined identifier");

  if (ITEM_TYPE_VAR != data->get_item_type())
    yyerror("ast_variable() failed - wrong type");

  // todo check if array
  value = strdup(((variable_data *)data)->get_value().c_str());
}

const char ast_variable::get_type() const
{
  return VAR_STAT_TYPE;
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
class ast_operator : public ast_expression
{
  const ast_expression *const left_child;
  const ast_expression *const rght_child;
  const char operation;

public:
  virtual ~ast_operator();
  ast_operator(ast_expression *const, const char,
               ast_expression *const);

  const char get_type() const override;
  virtual char *evaluate() const override;
};

// recursive deconstructor
ast_operator::~ast_operator()
{
  delete left_child;
  delete rght_child;
}

ast_operator::ast_operator(ast_expression *const o0,
                           const char op,
                           ast_expression *const o1)
    : left_child(o0), rght_child(o1), operation(op)
{
  if(ASG_CHR == op)
    yyerror("ast_operator() failed - use ast_assign() instead");
  if ((nullptr == o0 && '!' != op && '-' != op) ||
      nullptr == o1)
    yyerror("ast_operator() failed - received nullptr");
}

const char ast_operator::get_type() const
{
  return OPR_STAT_TYPE;
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

  if (v0 && OPR_STAT_TYPE == left_child->get_type())
    free(v0);
  if (v1 && OPR_STAT_TYPE == rght_child->get_type())
    free(v1);
  return result;
}

// here left_child is always will always be evaluated last
class ast_assign : public ast_expression
{
  const ast_variable *const left_child;
  const ast_expression *const rght_child;

public:
  virtual ~ast_assign();
  ast_assign(ast_variable *const,
             ast_expression *const);

  const char get_type() const override;
  virtual char *evaluate() const override;
};

ast_assign::~ast_assign()
{
  delete rght_child;
  delete left_child;
}

ast_assign::ast_assign(
    ast_variable *const v0, ast_expression *const v1)
    : left_child(v0), rght_child(v1)
{
  if(nullptr == v0 || nullptr == v1)
    yyerror("ast_assign() failed - received nullptr");
}

const char ast_assign::get_type() const
{
  return ASG_STAT_TYPE;
}

char *ast_assign::evaluate() const
{
  char* v1 = rght_child->evaluate();
  char* v0 = left_child->evaluate();
  return asg_vals(v0, v1);
}

//------------------------------------------------

class ast_scope : public ast_statement
{
  const std::vector<ast_statement *> *statemets;

public:
  ~ast_scope();
  ast_scope(const std::vector<ast_statement *> *const);

  const char get_type() const override;
  char *evaluate() const override;
};

ast_scope::~ast_scope()
{
  if (nullptr == statemets)
    return;

  for (size_t i = 0; i < statemets->size(); i++)
    delete statemets->at(i);
}

ast_scope::ast_scope(const std::vector<
                     ast_statement *> *const s)
    : statemets(s)
{
  if (nullptr == s)
    return;

  statemets = s;
  for (size_t i = 0; i < statemets->size(); i++)
    if (nullptr == statemets->at(i))
    {
      yyerror("ast_scope() failed - received nullptr");
      return;
    }
}
const char ast_scope::get_type() const
{
  return SCP_STAT_TYPE;
}

char *ast_scope::evaluate() const
{
  if (nullptr == statemets)
    return nullptr;

  for (size_t i = 0; i < statemets->size(); i++)
  {
    char *evaluation = statemets->at(i)->evaluate();
    if (OPR_STAT_TYPE == statemets->at(i)->get_type())
      free(evaluation);
  }

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

  const char get_type() const override;
  char *evaluate() const override;
};

ast_ifelse::~ast_ifelse()
{
  delete judge;
  delete sucss_case;
  if (failr_case)
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

const char ast_ifelse::get_type() const
{
  return IFE_STAT_TYPE;
}

char *ast_ifelse::evaluate() const
{
  char *evaluation = judge->evaluate();
  int result = strcmp(evaluation, "true");
  if (OPR_STAT_TYPE == judge->get_type())
    free(evaluation);

  if (0 == result)
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

  const char get_type() const override;
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

const char ast_while::get_type() const
{
  return WHL_STAT_TYPE;
}

char *ast_while::evaluate() const
{
  char *evaluation = nullptr;
  while (0 == strcmp(evaluation = judge->evaluate(), "true"))
  {
    if (OPR_STAT_TYPE == judge->get_type())
      free(evaluation);
    evaluation = sucss_case->evaluate();
    if (OPR_STAT_TYPE == sucss_case->get_type())
      free(evaluation);
  }

  if (evaluation && OPR_STAT_TYPE == judge->get_type())
    free(evaluation);

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

  const char get_type() const override;
  char *evaluate() const override;
};

ast_for::~ast_for()
{
  if (initl)
    delete initl;
  delete judge;
  if (incrm)
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

const char ast_for::get_type() const
{
  return FOR_STAT_TYPE;
}

char *ast_for::evaluate() const
{
  char *evaluation =
      initl ? initl->evaluate() : nullptr;
  if (evaluation && OPR_STAT_TYPE == initl->get_type())
    free(evaluation);

  while (0 == strcmp(evaluation = judge->evaluate(), "true"))
  {
    if (OPR_STAT_TYPE == judge->get_type())
      free(evaluation);
    sucss_case->evaluate();

    evaluation =
        incrm ? incrm->evaluate() : nullptr;
    if (evaluation && OPR_STAT_TYPE == incrm->get_type())
      free(evaluation);
  }

  if (evaluation && OPR_STAT_TYPE == judge->get_type())
    free(evaluation);
  return nullptr;
}

class ast_def : public ast_statement
{
public:
  ~ast_def() = default;
  ast_def(const char *const,
          const char *const,
          const char *const);
  ast_def();

  const char get_type() const override;
  char *evaluate() const override;
};

/* variable constructor */
ast_def::ast_def(const char *const data_type,
                 const char *const id,
                 const char *const value = nullptr)
{
  if (nullptr == data_type || nullptr == id)
    yyerror("ast_def() failed - received nullptr");
  if (false == is_primitive(data_type))
    yyerror("ast_def() failed - wrong type");
  if (scope_search(id))
    yyerror("ast_def() failed - identifier already defined");

  item_data *definition = nullptr;
  if (value)
    definition = new variable_data(data_type, value);
  else
    definition = new variable_data(data_type);
  symbols[LAST_SCOPE].insert(id, definition);
}

const char ast_def::get_type() const
{
  return DEF_STAT_TYPE;
}

char *ast_def::evaluate() const
{
  return nullptr;
}

// todo ast_assign

#endif