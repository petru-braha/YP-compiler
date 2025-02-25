#ifndef __0ASTASTCALL0__
#define __0ASTASTCALL0__

#include <vector>
#include "class/dev/ast.hpp"
#include "class/dev/yyerror.hpp"
#include "class/dev/symbol_data.hpp"

#include "class/function_data.hpp"
#include "class/symbol_table.hpp"
#include "class/scope_stack.hpp"
#include "class/type_table.hpp"
#include "ast_action.hpp"

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
  if (is_type(id))
  {
    yyerror("ast_symbolcall() failed - class id");
    return nullptr;
  }

  symbol_data *data = symbol_exists(id);
  if (nullptr == data)
    yyerror("ast_symbolcall() failed - undefined id");
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
  symbol_data *data = (symbol_data *)id->evaluate();
  if (nullptr == data)
    return nullptr;

  if (FNCT_SYMB_TYPE != data->get_item_type())
  {
    yyerror("ast_methodcall() failed - wrong type");
    return nullptr;
  }

  function_data *f = (function_data *)data;
  std::vector<mutable_data *> v(parameters->size());
  for (size_t i = 0; i < v.size(); i++)
  {
    void *buffer = parameters->at(i)->evaluate();

    if (is_returning_char(parameters->at(i)))
    {
      char *value = (char *)buffer;
      v[i] = new primitive_data(type_of(value), value);
      continue;
    }

    // is_returning_char == false
    symbol_data *temp = (symbol_data *)buffer;
    if (FNCT_SYMB_TYPE == temp->get_item_type())
    {
      yyerror("ast_methodcall() failed - received function");
      return nullptr;
    }

    v[i] = (mutable_data *)buffer;
  }

  return f->call(&v);
}

const char ast_methodcall::get_stat_type() const
{
  return MTD_STAT_TYPE;
}

/*
 !-----------------------------------
 ! the promised implementatiom
 * function_data::~function_data();
 * function_data::emplace();
 * function_data::call();
 */

function_data::~function_data()
{
  for (auto &item_pair : *parameters)
    delete item_pair.second;
  delete parameters;

  if (nullptr == execution)
    return;

  for (auto &statement : *execution)
    delete statement;
  delete execution;
}

bool function_data::emplace(
    const std::vector<mutable_data *> *const arguments)
{
  if (parameters->size() != arguments->size())
    return false;

  size_t index = 0;
  for (const auto &item_pair : *parameters)
  {
    if (item_pair.second->get_item_type() !=
            arguments->at(index)->get_item_type() ||
        item_pair.second->get_data_type() !=
            arguments->at(index)->get_data_type())
      return false;
    index++;
  }

  index = 0;
  for (auto &item_pair : *parameters)
  {
    delete item_pair.second;
    item_pair.second = nullptr;
    if (false ==
        make_copy(
            item_pair.second,
            arguments->at(index)))
      return false;
    index++;
  }

  return true;
}

void *function_data::call(
    const std::vector<mutable_data *> *const arguments)
{
  if (false == emplace(arguments))
  {
    yyerror("function_call() failed - type missmatch");
    return nullptr;
  }

  scope_insert();
  for (auto &item_pair : *parameters)
  {
    mutable_data *data = nullptr;
    if (false == make_copy(data, item_pair.second))
    {
      yyerror("function_call() failed - "
              "make_copy() failed");
      return nullptr;
    }

    symbol_insert(item_pair.first, data);
  }

  void *buffer = nullptr;
  bool is_returned = false;
  for (auto &statement : *execution)
  {
    buffer = statement->evaluate();
    if (RET_STAT_TYPE == statement->get_stat_type())
    {
      return_value *temp = (return_value *)buffer;
      buffer = temp->value;
      is_returned = true;
      break;
    }
  }

  if (false == is_returned)
  {
    scope_remove();
    yyerror("function_call() failed - no return statement");
    return nullptr;
  }

  symbol_data *data = (symbol_data *)buffer;
  if (FNCT_SYMB_TYPE == data->get_item_type() ||
      data->get_data_type() != return_data_type)
  {
    yyerror("function_call() failed - return type missmatch");
    return nullptr;
  }

  scope_remove();
  return data;
}

//!-----------------------------------
//! end of the promised implementatiom

constexpr char VNL_TYPEOF = 0;
constexpr char VNL_PRINTF = 1;

class ast_vanillacall : public ast_expression
{
  ast_expression *const expression;
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

#endif
