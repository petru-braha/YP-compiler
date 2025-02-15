#ifndef __0ASTASTINDEX0__
#define __0ASTASTINDEX0__

#include "class/dev/ast.hpp"

#include "class/primitive_data.hpp"
#include "class/array_data.hpp"
#include "ast_call.hpp"

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
  if (ARRY_SYMB_TYPE != data->get_item_type())
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
  symbol_data *data = (symbol_data *)object_id->evaluate();
  if (nullptr == data)
    return nullptr;

  if (OBJT_SYMB_TYPE != data->get_item_type())
  {
    yyerror("ast_fielding() failed - wrong type");
    return nullptr;
  }

  object_data *o = (object_data *)data;
  field_data *f = o->get_attriubte(field_id);
  if (ACCS_MODF_PRIV == f->access_modifier)
  {
    yyerror("ast_fielding() failed - private field");
    return nullptr;
  }

  if (FNCT_SYMB_TYPE == f->data->get_item_type())
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
  symbol_data *data = (symbol_data *)object_id->evaluate();
  if (nullptr == data)
    return nullptr;

  if (OBJT_SYMB_TYPE != data->get_item_type())
  {
    yyerror("ast_fieldcall() failed - wrong type");
    return nullptr;
  }

  object_data *o = (object_data *)data;
  field_data *f = o->get_attriubte(field_id);
  if (ACCS_MODF_PRIV == f->access_modifier)
  {
    yyerror("ast_fieldcall() failed - private field");
    return nullptr;
  }

  if (FNCT_SYMB_TYPE != f->data->get_item_type())
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
