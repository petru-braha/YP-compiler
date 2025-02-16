#ifndef __0DEFINITION0__
#define __0DEFINITION0__

/* comments:
 * nullptr => error occured
 * symbol_data memory removal is performed by tables
 * and not here
 * todo add to the specified scope
 */

#include <vector>
#include "class/dev/ast.hpp"
#include "class/dev/yyerror.hpp"
#include "class/dev/symbol_data.hpp"

#include "class/class_data.hpp"
#include "class/symbol_table.hpp"
#include "class/type_table.hpp"
#include "ast_call.hpp"

extern std::vector<symbol_table> symbols;
#define LAST_SCOPE symbols.size() - 1

class ast_definition : public ast_statement
{
public:
  virtual ~ast_definition() = default;
};

class ast_primitivedefn : public ast_definition
{
  char *const data_type;
  char *const id;
  ast_expression *value;

public:
  virtual ~ast_primitivedefn() override;
  ast_primitivedefn(char *const, char *const);
  ast_primitivedefn(char *const, char *const,
                    ast_expression *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_primitivedefn::~ast_primitivedefn()
{
  free(data_type);
  free(id);
  delete value;
}

ast_primitivedefn::ast_primitivedefn(
    char *const type, char *const id)
    : data_type(type), id(id)
{
  if (nullptr == type || nullptr == id)
    yyerror("ast_primitivedefn() failed - received nullptr");

  std::string buffer = default_value_of(data_type);
  value = new ast_constant(strdup(buffer.c_str()));
}

ast_primitivedefn::ast_primitivedefn(
    char *const type, char *const id,
    ast_expression *const value)
    : data_type(type), id(id), value(value)
{
  if (nullptr == type || nullptr == id ||
      nullptr == value)
    yyerror("ast_primitivedefn() failed - received nullptr");
}

void *ast_primitivedefn::evaluate()
{
  if (is_type(id))
  {
    yyerror("ast_primitivedefn() failed - type treated as id");
    return nullptr;
  }

  if (scope_search(id))
  {
    yyerror("ast_primitivedefn() failed - already defined id");
    return nullptr;
  }

  const char *buffer = get_buffer(value);
  if (is_compatible(data_type, buffer))
  {
    yyerror("ast_primitivedefn() failed - type missmatch");
    return nullptr;
  }

  primitive_data *data =
      new primitive_data(data_type, buffer);
  symbols[LAST_SCOPE].insert(id, data);
  return data;
}

const char ast_primitivedefn::get_stat_type() const
{
  return PMD_STAT_TYPE;
}

class ast_functiondefn : public ast_definition
{
  char *const return_type;
  char *const id;
  std::vector<ast_definition *> *const parameters;
  std::vector<ast_statement *> *const execution;

public:
  virtual ~ast_functiondefn() override;
  ast_functiondefn(
      char *const, char *const,
      std::vector<ast_definition *> *const);
  ast_functiondefn(
      char *const, char *const,
      std::vector<ast_definition *> *const,
      std::vector<ast_statement *> *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_functiondefn::~ast_functiondefn()
{
  free(return_type);
  free(id);
  for (size_t i = 0; i < parameters->size(); i++)
    delete parameters->at(i);
  delete parameters;

  if (execution)
    delete execution;
}

ast_functiondefn::ast_functiondefn(
    char *const type, char *const id,
    std::vector<ast_definition *> *const arguments)
    : return_type(type), id(id),
      parameters(arguments), execution(nullptr)
{
}

ast_functiondefn::ast_functiondefn(
    char *const type, char *const id,
    std::vector<ast_definition *> *const arguments,
    std::vector<ast_statement *> *const exe)
    : return_type(type), id(id),
      parameters(arguments), execution(exe)
{
}

void *ast_functiondefn::evaluate()
{
  // todo add_body if already exists
  return nullptr;
}

const char ast_functiondefn::get_stat_type() const
{
  return FCD_STAT_TYPE;
}

class ast_objectdefn : public ast_definition
{
  char *const data_type;
  char *const id;
  std::vector<ast_expression *> *const arguments;

public:
  virtual ~ast_objectdefn() override;
  ast_objectdefn(char *const, char *const);
  ast_objectdefn(char *const, char *const,
                 std::vector<ast_expression *> *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_objectdefn::~ast_objectdefn()
{
  free(data_type);
  free(id);
  for (size_t i = 0; i < arguments->size(); i++)
    delete arguments->at(i);
  delete arguments;
}

// when the class has a default constructor
ast_objectdefn::ast_objectdefn(
    char *const type, char *const id)
    : data_type(type), id(id),
      arguments(new std::vector<ast_expression *>())
{
  if (nullptr == type || nullptr == id)
    yyerror("ast_objectdefn() failed - received nullptr");
}

ast_objectdefn::ast_objectdefn(
    char *const type, char *const id,
    std::vector<ast_expression *> *const arguments)
    : data_type(type), id(id), arguments(arguments)
{
  if (nullptr == type || nullptr == id ||
      nullptr == arguments)
    yyerror("ast_objectdefn() failed - received nullptr");
}

void *ast_objectdefn::evaluate()
{
  // data type
  class_data *model = type_exists(data_type);
  if (nullptr == model)
  {
    yyerror("ast_objectdefn() failed - undefined type");
    return nullptr;
  }

  if (is_primitive(data_type))
  {
    yyerror("ast_objectdefn() failed - primitive treated as object");
    return nullptr;
  }

  // id
  if (is_type(id))
  {
    yyerror("ast_objectdefn() failed - type treated as id");
    return nullptr;
  }

  if (scope_search(id))
  {
    yyerror("ast_objectdefn() failed - already defined id");
    return nullptr;
  }

  // if previously defined in class
  if (model->get_data(id).first != model->end())
  {
    yyerror("ast_objectdefn() - already defined id in class");
    return nullptr;
  }

  object_data *o = nullptr;
  std::pair<class_data::it, class_data::it> constructors;
  constructors = model->get_data(data_type);

  for (auto &it = constructors.first;
       it != constructors.second; it++)
  {
    if (ACCS_MODF_PRIV == (*it).second.access_modifier)
      continue;
    function_data *f = (function_data *)(*it).second.data;
    if (f->get_count() != arguments->size())
      continue;

    std::vector<mutable_data *> v(arguments->size());
    function_data::it itr = f->begin();

    for (size_t idx = 0; idx < v.size(); idx++, itr++)
    {
      void *buffer = arguments->at(idx)->evaluate();

      if (is_returning_char(arguments->at(idx)))
      {
        char *value = (char *)buffer;
        v[idx] = new primitive_data(type_of(value), value);
      }
      else
        v[idx] = (mutable_data *)buffer;

      if (v[idx]->get_item_type() != (*itr).second->get_item_type() ||
          v[idx]->get_data_type() != (*itr).second->get_data_type())
      {
        for (size_t i = 0; i <= idx; i++)
          delete v[idx];
        break; // search for a new constructor
      }
    }

    o = (object_data *)f->call(&v);
  }

  if (nullptr == o)
    yyerror("ast_objectdefn() - undefined appropriate constructor");

  return o;
}

// todo change last method maybe?
// todo if array
const char ast_objectdefn::get_stat_type() const
{
  return OBD_STAT_TYPE;
}

class ast_classdefn : public ast_statement
{
  char *const id;
  std::vector<ast_definition *> *const fields;

public:
  virtual ~ast_classdefn() override;
  ast_classdefn(char *const);
  ast_classdefn(
      char *const,
      std::vector<ast_definition *> *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_classdefn::~ast_classdefn()
{
  free(id);
  for (size_t i = 0; i < fields->size(); i++)
    delete fields->at(i);
  delete fields;
}

ast_classdefn::ast_classdefn(char *const id)
    : id(id), fields(nullptr)
{
  if (nullptr == id)
    yyerror("ast_classdefn() failed - received nullptr");
  if (0 != LAST_SCOPE)
    yyerror("ast_classdefn() failed - class declared in scope");
}

ast_classdefn::ast_classdefn(
    char *const id,
    std::vector<ast_definition *> *const data)
    : id(id), fields(data)
{
  if (nullptr == id || nullptr == data)
    yyerror("ast_classdefn() failed - received nullptr");
  if (0 != LAST_SCOPE)
    yyerror("ast_classdefn() failed - class declared in scope");
}

void *ast_classdefn::evaluate()
{
  if (type_exists(id) || scope_search(id))
  {
    yyerror("ast_classdefn() failed - id already defined");
    return nullptr;
  }

  // todo evaluation
  // todo access modifier
  // todo function class declaration

  typedef std::unordered_multimap<std::string, field_data> map;
  map *definition = new map();
  class_data *data = new class_data(definition);
  if (false == type_insert(id, data))
  {
    delete data;
    return nullptr;
  }

  return data;
}

const char ast_classdefn::get_stat_type() const
{
  return CLD_STAT_TYPE;
}

class ast_scopedefn : public ast_statement
{
  ast_definition *const def;

public:
  virtual ~ast_scopedefn() override;
  ast_scopedefn(ast_definition *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_scopedefn::~ast_scopedefn()
{
  delete def;
}

ast_scopedefn::ast_scopedefn(ast_definition *const def)
    : def(def)
{
  if (nullptr == def)
    yyerror("ast_scopedefn() failed - received nullptr");
}

void *ast_scopedefn::evaluate()
{

  // add to symbols
  return nullptr;
}

const char ast_scopedefn::get_stat_type() const
{
  return SCD_STAT_TYPE;
}

#endif
