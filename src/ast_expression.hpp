#ifndef __0EXPRESSION0__
#define __0EXPRESSION0__

/* comments:
 * nullptr => error occured
 * item_data memory removal is performed by tables
 * and not here
 todo ast_expression can be primitive, i don't treat that case
 todo is_char()
 */

#include "class/dev/yyerror.hpp"
#include "class/dev/item_data.hpp"
#include "class/dev/function.hpp"
#include "class/dev/ast.hpp"
#include "class/dev/ast_alphabet.hpp"
#include "class/dev/ast_arithmetic.hpp"

#include "implementation.hpp"

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

/* ANY data type
 * stored as leaf nodes
 */
class ast_symbolcall : public ast_expression
{
  const char *const id;

public:
  virtual ~ast_symbolcall() override;
  ast_symbolcall(const char *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_symbolcall::~ast_symbolcall()
{
  delete id;
}

ast_symbolcall::ast_symbolcall(const char *const id)
    : id(id)
{
  if (nullptr == id)
    yyerror("ast_symbolcall() failed - received nullptr");
}

void *ast_symbolcall::evaluate()
{
  void *data = scope_search(id);
  if (nullptr == data)
  {
    yyerror("ast_symbolcall() failed - undefined id");
    return nullptr;
  }

  if (type_exists(id))
  {
    yyerror("ast_symbolcall() failed - class id");
    return nullptr;
  }

  return data;
}

const char ast_symbolcall::get_stat_type() const
{
  return SYC_STAT_TYPE;
}

class ast_methodcall : public ast_expression
{
  ast_symbolcall *const id;
  const std::vector<ast_expression *> *const parameters;

public:
  virtual ~ast_methodcall() override;
  ast_methodcall(
      ast_symbolcall *const,
      const std::vector<ast_expression *> *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_methodcall::~ast_methodcall()
{
  delete id;
  for (size_t i = 0; i < parameters->size(); i++)
    delete (*parameters)[i];
  delete parameters;
}

ast_methodcall::ast_methodcall(
    ast_symbolcall *const id,
    const std::vector<ast_expression *> *const arguments)
    : id(id), parameters(arguments)
{
  if (nullptr == id || nullptr == arguments)
    yyerror("ast_methodcall() failed - received nullptr");
}

void *ast_methodcall::evaluate()
{
  item_data *data = (item_data *)id->evaluate();
  if (nullptr == data)
    return nullptr;

  if (FNCT_ITEM_TYPE != data->get_item_type())
  {
    yyerror("ast_methodcall() failed - wrong type");
    return nullptr;
  }

  // todo it can also be char*
  std::vector<mutable_data *> v(parameters->size());
  for (size_t i = 0; i < v.size(); i++)
  {
    void *buffer = parameters->at(i)->evaluate();
    /*
    if (true)
    {
      char *value = (char *)buffer;
      std::string type = type_of(value);
      v[i] = new primitive_data(type, value);
    }*/

    v[i] = (mutable_data *)buffer;
  }

  function_data *f = (function_data *)data;
  return f->call(&v);
}

const char ast_methodcall::get_stat_type() const
{
  return MTD_STAT_TYPE;
}

/*
 ! the promised implementatiom
 * function_data::~function_data();
 * function_data::call();
 */

function_data::~function_data()
{
  for (auto &item_pair : *parameters)
    delete item_pair.second;
  delete parameters;
  for (auto &statement : *execution)
    delete statement;
  delete execution;
}

void *function_data::call(
    const std::vector<mutable_data *> *const arguments)
{
  if (parameters->size() != arguments->size())
  {
    yyerror("function_call() failed - type missmatch");
    return nullptr;
  }

  size_t index = 0;
  for (const auto &item_pair : *parameters)
  {
    if (item_pair.second->get_item_type() !=
        arguments->at(index)->get_item_type())
    {
      yyerror("function_call() failed - type missmatch");
      return nullptr;
    }

    if (item_pair.second->get_data_type() !=
        arguments->at(index)->get_data_type())
    {
      yyerror("function_call() failed - type missmatch");
      return nullptr;
    }

    index++;
  }

  index = 0;
  for (auto &item_pair : *parameters)
  {
    delete item_pair.second;
    item_pair.second = arguments->at(0);
  }

  symbols.emplace_back();

  for (auto &item_pair : *parameters)
    symbols[LAST_SCOPE].insert(item_pair.first, item_pair.second);

  void *buffer = nullptr;
  for (auto &statement : *execution)
  {
    buffer = statement->evaluate();
    if (RET_STAT_TYPE == statement->get_stat_type())
      break;
  }

  symbols.pop_back();
  return nullptr;
}

constexpr char VNL_TYPEOF = 0;
constexpr char VNL_PRINTF = 1;

class ast_vanillacall : public ast_expression
{
  ast_expression *expression;
  const char data;
  void *result;

public:
  virtual ~ast_vanillacall() override;
  ast_vanillacall(ast_expression *const, const char);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_vanillacall::~ast_vanillacall()
{
  delete expression;
  free(result);
}

ast_vanillacall::ast_vanillacall(ast_expression *const e, const char d)
    : expression(e), data(d), result(nullptr)
{
  if (nullptr == e)
    yyerror("ast_vanillacall() failed - received nullptr");
}

void *ast_vanillacall::evaluate()
{
  if (VNL_TYPEOF == data)
    result = type_of(get_buffer(expression), 0);
  else if (VNL_PRINTF == data)
    result = print_f(get_buffer(expression), 0);
  else
  {
    yyerror("ast_vanillacall() failed - undefined method");
    return nullptr;
  }

  return result;
};

const char ast_vanillacall::get_stat_type() const
{
  return MTS_STAT_TYPE;
}

// here, left_child is evaluated last
class ast_assign : public ast_expression
{
  ast_symbolcall *left_child;
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
  // rght_child is user-defined
  mutable_data *left =
      (mutable_data *)left_child->evaluate();
  void *rght = rght_child->evaluate();
  if (rght_child->get_stat_type() != CST_STAT_TYPE &&
      rght_child->get_stat_type() != OPR_STAT_TYPE)
  {
    mutable_data *data = (mutable_data *)rght;

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

  // rght_child is primitive
  char *data = (char *)rght;
  if (!is_primitive(left->get_data_type()))
  {
    yyerror("ast_assign() failed - not primitive type");
    return nullptr;
  }

  if (!is_compatible(
          left->get_data_type().c_str(),
          data))
  {
    yyerror("ast_assign() failed - type missmatch");
    return nullptr;
  }

  primitive_data *value = (primitive_data *)left;
  value->set_value(data);
  return left;
}

const char ast_assign::get_stat_type() const
{
  return ASG_STAT_TYPE;
}

class ast_indexing : public ast_expression
{
  ast_symbolcall *const id;
  ast_expression *const index;

public:
  virtual ~ast_indexing() override;
  ast_indexing(
      ast_symbolcall *const, ast_expression *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_indexing::~ast_indexing()
{
  free(id);
  delete index;
}

ast_indexing::ast_indexing(
    ast_symbolcall *const id, ast_expression *const e)
    : id(id), index(e)
{
  if (nullptr == id || nullptr == e)
    yyerror("ast_indexing() failed - received nullptr");
}

void *ast_indexing::evaluate()
{
  const char *buffer = get_buffer(index);
  if (strcmp(INTG_DATA_TYPE, type_of(buffer).c_str()))
  {
    yyerror("ast_indexing() failed - bad index");
    return nullptr;
  }

  if ('-' == buffer[0] || 0 == strcmp(buffer, "0"))
  {
    yyerror("ast_indexing() failed - bad index");
    return nullptr;
  }

  mutable_data *data = (mutable_data *)id->evaluate();
  if (ARRY_ITEM_TYPE != data->get_item_type())
  {
    yyerror("ast_indexing() failed - not array type");
    return nullptr;
  }

  array_data *a = (array_data *)data;
  a->operator[](atoi(buffer));
  return a;
}

const char ast_indexing::get_stat_type() const
{
  return IDX_STAT_TYPE;
}

class ast_fielding : public ast_expression
{
  ast_symbolcall *const object_id;
  char *const field_id;

public:
  virtual ~ast_fielding() override;
  ast_fielding(
      ast_symbolcall *const, char *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_fielding::~ast_fielding()
{
  delete object_id;
  free(field_id);
}

ast_fielding::ast_fielding(
    ast_symbolcall *const id0, char *const id1)
    : object_id(id0), field_id(id1)
{
  if (nullptr == id0 || nullptr == id1)
    yyerror("ast_fielding() failed - received nullptr");
}

void *ast_fielding::evaluate()
{
  item_data *data = (item_data *)object_id->evaluate();
  if (nullptr == data)
    return nullptr;

  if (OBJT_ITEM_TYPE != data->get_item_type())
  {
    yyerror("ast_fielding() failed - wrong type");
    return nullptr;
  }

  object_data *o = (object_data *)data;
  field *f = o->get_attriubte(field_id);
  if (ACCS_MODF_PRIV == f->access_modifier)
  {
    yyerror("ast_fielding() failed - private field");
    return nullptr;
  }

  if (FNCT_ITEM_TYPE == f->data->get_item_type())
  {
    yyerror("ast_fielding() failed - use ast_fieldcall()");
    return nullptr;
  }

  return f->data;
}

const char ast_fielding::get_stat_type() const
{
  return FLD_STAT_TYPE;
}

class ast_fieldcall : public ast_expression
{
  ast_symbolcall *const object_id;
  char *const field_id;
  std::vector<ast_expression *> *const parameters;

public:
  virtual ~ast_fieldcall() override;
  ast_fieldcall(
      ast_symbolcall *const, char *const,
      std::vector<ast_expression *> *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_fieldcall::~ast_fieldcall()
{
  delete object_id;
  free(field_id);
  for (size_t i = 0; i < parameters->size(); i++)
    delete parameters->at(i);
  delete parameters;
}

ast_fieldcall::ast_fieldcall(
    ast_symbolcall *const id0, char *const id1,
    std::vector<ast_expression *> *const arguments)
    : object_id(id0), field_id(id1),
      parameters(arguments)
{
  if (nullptr == id0 || nullptr == id1 ||
      nullptr == parameters)
    yyerror("ast_fieldcall() failed - received nullptr");
}

void *ast_fieldcall::evaluate()
{
  item_data *data = (item_data *)object_id->evaluate();
  if (nullptr == data)
    return nullptr;

  if (OBJT_ITEM_TYPE != data->get_item_type())
  {
    yyerror("ast_fieldcall() failed - wrong type");
    return nullptr;
  }

  object_data *o = (object_data *)data;
  field *f = o->get_attriubte(field_id);
  if (ACCS_MODF_PRIV == f->access_modifier)
  {
    yyerror("ast_fieldcall() failed - private field");
    return nullptr;
  }

  if (FNCT_ITEM_TYPE != f->data->get_item_type())
  {
    yyerror("ast_fieldcall() failed - use ast_fielding()");
    return nullptr;
  }

  // todo evaluate the parameters
  // std::vector<0>
  return f->data;
}

const char ast_fieldcall::get_stat_type() const
{
  return FLC_STAT_TYPE;
}

#endif
