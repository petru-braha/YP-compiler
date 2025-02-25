#ifndef __0DEFINITION0__
#define __0DEFINITION0__

/* comments:
 * nullptr => error occured
 * symbol_data memory removal is performed by tables
 * and not here
 * insertion is performent by ast_scopedefn
 */

#include <vector>
#include "class/dev/ast.hpp"
#include "class/dev/yyerror.hpp"
#include "class/dev/function.hpp"
#include "class/dev/symbol_data.hpp"

#include "class/primitive_data.hpp"
#include "class/function_data.hpp"
#include "class/object_data.hpp"

#include "class/class_data.hpp"
#include "class/symbol_table.hpp"
#include "class/type_table.hpp"
#include "ast_call.hpp"

struct ast_defn
{
  const char *id;
  symbol_data *data;
};

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
  ast_defn result;

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
  if (value)
    delete value;
}

ast_primitivedefn::ast_primitivedefn(
    char *const type, char *const id)
    : data_type(type), id(id), value(nullptr)
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
  std::string base(base_type(data_type));
  if (false == is_primitive(data_type) &&
      false == is_primitive(base))
  {
    yyerror("ast_primitivedefn() failed - not primitive type");
    return nullptr;
  }

  if (is_type(id))
  {
    yyerror("ast_primitivedefn() failed - type treated as id");
    return nullptr;
  }

  if (symbol_exists(id))
  {
    yyerror("ast_primitivedefn() failed - already defined id");
    return nullptr;
  }

  const char *buffer = nullptr;
  if (value)
    buffer = get_buffer(value);
  if (buffer && false == is_compatible(data_type, buffer))
  {
    yyerror("ast_primitivedefn() failed - type missmatch");
    return nullptr;
  }

  // not array of primitives
  mutable_data *data = nullptr;
  if (buffer)
    data = new primitive_data(data_type, buffer);
  else
    data = new primitive_data(data_type);

  if ("" == base)
  {
    result = {id, data};
    return &result;
  }

  std::vector<size_t> level_data;
  level_data.reserve(3 * base.size());
  char *number = strtok(data_type, "[]");
  number = strtok(NULL, "[]"); // skip the base type
  while (number)
  {
    level_data.emplace_back(atoll(number));
    number = strtok(NULL, "[]");
  }

  data = new array_data(level_data, data);
  result = {id, data};
  return &result;
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
  ast_defn result;

public:
  virtual ~ast_functiondefn() override;
  ast_functiondefn(
      char *const, char *const,
      std::vector<ast_definition *> *const);
  ast_functiondefn(
      char *const, char *const,
      std::vector<ast_definition *> *const,
      std::vector<ast_statement *> *const);
  ast_functiondefn(
      std::vector<ast_statement *> *const,
      std::vector<ast_definition *> *const,
      char *const);

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

  // execution is removed by the function_data class
}

// ast function declaration
ast_functiondefn::ast_functiondefn(
    char *const type, char *const id,
    std::vector<ast_definition *> *const arguments)
    : return_type(type), id(id),
      parameters(arguments), execution(nullptr)
{
  if (nullptr == type || nullptr == id ||
      nullptr == arguments)
    yyerror("ast_functiondefn() failed - received nullptr");
}

// ast function definition
ast_functiondefn::ast_functiondefn(
    char *const type, char *const id,
    std::vector<ast_definition *> *const arguments,
    std::vector<ast_statement *> *const exe)
    : return_type(type), id(id),
      parameters(arguments), execution(exe)
{

  if (nullptr == type || nullptr == id ||
      nullptr == arguments || nullptr == execution)
    yyerror("ast_functiondefn() failed - received nullptr");
}

// ast constructor
ast_functiondefn::ast_functiondefn(
    std::vector<ast_statement *> *const exe,
    std::vector<ast_definition *> *const arguments,
    char *const id)
    : return_type(id), id(id),
      parameters(arguments), execution(exe)
{
  if (nullptr == exe || nullptr == arguments ||
      nullptr == id)
    yyerror("ast_functiondefn() failed - received nullptr");
}

/* if constructor:
 * false == is_type(return_type)
 * return_type == id
 * is_type(id) == true is allowed 
 */
void *ast_functiondefn::evaluate()
{
  if (false == is_type(return_type) &&
      return_type != id)
  {
    yyerror("ast_functiondefn() failed - undefined type");
    return nullptr;
  }

  symbol_data *previous_data = symbol_exists(id);
  function_data *previous_f = (function_data *)previous_data;
  if (previous_data &&
      (previous_f->is_defined() ||
       FNCT_SYMB_TYPE != previous_data->get_item_type()))
  {
    yyerror("ast_functiondefn() failed - already defined id");
    return nullptr;
  }

  // another declaration
  if (previous_data && nullptr == execution)
    return previous_data;

  // add the body
  if (previous_data)
  {
    if (false == previous_f->define(execution))
    {
      yyerror("ast_functiondefn() failed - "
              "can't define function");
      return nullptr;
    }

    result = {id, previous_f};
    return &result;
  }

  // not previously declared
  function_data::map *arguments =
      new function_data::map();
  ast_defn *buffer = nullptr;
  for (size_t i = 0; i < parameters->size(); i++)
  {
    buffer = (ast_defn *)parameters->at(i)->evaluate();

    if (arguments->find(buffer->id) != arguments->end())
    {
      for (auto &element : *arguments)
        delete element.second;
      delete arguments;
      yyerror("ast_functiondefn() failed - "
              "already defined parameter");
      return nullptr;
    }

    std::pair<std::string, mutable_data *>
        pair{buffer->id, (mutable_data *)buffer->data};
    arguments->insert(pair);
  }

  function_data *data = nullptr;
  if (nullptr == execution)
    data = new function_data(return_type, arguments);
  else
    data = new function_data(return_type, arguments, execution);

  result = {id, data};
  return &result;
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
  ast_defn result;

  object_data *find_constructor(
      class_data *const, const std::string &);

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

  if (nullptr == arguments)
    return;
  for (size_t i = 0; i < arguments->size(); i++)
    delete arguments->at(i);
  delete arguments;
}

// when the class has a default constructor
ast_objectdefn::ast_objectdefn(
    char *const type, char *const id)
    : data_type(type), id(id), arguments(nullptr)
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

object_data *ast_objectdefn::find_constructor(
    class_data *const model, const std::string &type)
{
  std::pair<class_data::it, class_data::it> constructors;
  constructors = model->get_data(type);
  size_t argc = arguments ? arguments->size() : 0;

  for (auto &it = constructors.first;
       it != constructors.second; it++)
  {
    if (ACCS_MODF_PRIV == (*it).second.access_modifier)
      continue;
    function_data *f = (function_data *)(*it).second.data;
    if (f->get_count() != argc)
      continue;

    std::vector<mutable_data *> v(argc);
    function_data::it itr = f->begin();

    for (size_t idx = 0; idx < argc; idx++, itr++)
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

    if (itr == f->end())
      return (object_data *)f->call(&v);
  }

  return nullptr;
}

void *ast_objectdefn::evaluate()
{
  printf("yes obj dont forget to change find_constructor\n");

  // data type
  std::string base(base_type(data_type));
  class_data *model = type_exists(base);
  if ("" == base)
    model = type_exists(data_type);
  if (nullptr == model)
  {
    yyerror("ast_objectdefn() failed - undefined type");
    return nullptr;
  }

  if (is_primitive(base) || is_primitive(data_type))
  {
    yyerror("ast_objectdefn() failed - primitive treated as object");
    return nullptr;
  }

  if (false == model->is_defined())
  {
    yyerror("ast_objectdefn() failed - incomplete type");
    return nullptr;
  }

  // identifier
  if (is_type(id))
  {
    yyerror("ast_objectdefn() failed - type treated as id");
    return nullptr;
  }

  if (symbol_exists(id))
  {
    yyerror("ast_objectdefn() failed - already defined id");
    return nullptr;
  }

  mutable_data *data = find_constructor(
      model, "" == base ? data_type : base);
  if (nullptr == data)
  {
    yyerror("ast_objectdefn() - "
            "undefined appropriate constructor");
    return nullptr;
  }

  // not array of primitives
  if ("" == base)
  {
    result = {id, data};
    return &result;
  }

  std::vector<size_t> level_data;
  level_data.reserve(3 * base.size());
  char *number = strtok(data_type, "[]");
  number = strtok(NULL, "[]"); // skip the base type
  while (number)
  {
    level_data.emplace_back(atoll(number));
    number = strtok(NULL, "[]");
  }

  data = new array_data(level_data, data);
  result = {id, data};
  return &result;
}

const char ast_objectdefn::get_stat_type() const
{
  return OBD_STAT_TYPE;
}

class ast_access : public ast_statement
{
  ast_definition *const def;
  const char access;

public:
  virtual ~ast_access() override;
  ast_access(ast_definition *const);
  ast_access(const char, ast_definition *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
  const char get_accs_type() const;
};

ast_access::~ast_access()
{
  delete def;
}

ast_access::ast_access(ast_definition *const d)
    : def(d), access(ACCS_MODF_INVALID)
{
  if (nullptr == d)
    yyerror("ast_access() failed - received nullptr");
}

ast_access::ast_access(const char a, ast_definition *const d)
    : access(a), def(d)
{
  if (nullptr == d)
    yyerror("ast_access() failed - received nullptr");
}

void *ast_access::evaluate()
{
  return def->evaluate();
}

const char ast_access::get_stat_type() const
{
  return ACD_STAT_TYPE;
}

const char ast_access::get_accs_type() const
{
  return access;
}

class ast_classdefn : public ast_statement
{
  char *const id;
  std::vector<ast_access *> *const fields;

public:
  virtual ~ast_classdefn() override;
  ast_classdefn(char *const);
  ast_classdefn(char *const,
                std::vector<ast_access *> *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_classdefn::~ast_classdefn()
{
  free(id);
  if (nullptr == fields)
    return;

  for (size_t i = 0; i < fields->size(); i++)
    delete fields->at(i);
  delete fields;
}

// class declaration
ast_classdefn::ast_classdefn(char *const id)
    : id(id), fields(nullptr)
{
  if (nullptr == id)
    yyerror("ast_classdefn() failed - received nullptr");
  if (1 != scope_stack::size())
    yyerror("ast_classdefn() failed - class declared in scope");
}

ast_classdefn::ast_classdefn(
    char *const id,
    std::vector<ast_access *> *const data)
    : id(id), fields(data)
{
  if (nullptr == id || nullptr == data)
    yyerror("ast_classdefn() failed - received nullptr");
  if (1 != scope_stack::size())
    yyerror("ast_classdefn() failed - class declared in scope");
}

void *ast_classdefn::evaluate()
{
  if (symbol_exists(id))
  {
    yyerror("ast_classdefn() failed - id already defined");
    return nullptr;
  }

  class_data *previous_data = type_exists(id);
  if (previous_data && previous_data->is_defined())
  {
    yyerror("ast_classdefn() failed - type already defined");
    return nullptr;
  }

  if (nullptr == fields)
  {
    if (previous_data)
      return previous_data;
    class_data *data = new class_data();
    if (false == type_insert(id, data))
    {
      delete data;
      yyerror("ast_classdefn() failed - type_insert() failed");
      return nullptr;
    }

    return data;
  }

  char modifier = ACCS_MODF_PRIV;
  class_data::map *arguments = new class_data::map;
  for (size_t i = 0; i < fields->size(); i++)
  {
    ast_defn *buffer = (ast_defn *)fields->at(i)->evaluate();
    if (ACCS_MODF_INVALID != fields->at(i)->get_accs_type())
      modifier = fields->at(i)->get_accs_type();

    field_data data = {buffer->data, modifier};
    std::pair<std::string, field_data> pair{buffer->id, data};
    arguments->insert(pair);
  }

  // add the body
  if (previous_data)
  {
    if (false == previous_data->define(arguments))
      yywarning("ast_classdefn() - did not added body");
    return previous_data;
  }

  // not previously declared
  class_data *data = new class_data(arguments);
  if (false == type_insert(id, data))
  {
    for (auto &field : *arguments)
      delete field.second.data;
    delete data;
    yyerror("ast_classdefn() - "
            "type_insert() failed");
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

ast_scopedefn::ast_scopedefn(ast_definition *const d)
    : def(d)
{
  if (nullptr == d)
    yyerror("ast_scopedefn() failed - received nullptr");
}

void *ast_scopedefn::evaluate()
{
  ast_defn *buffer = (ast_defn *)def->evaluate();
  if (is_type(buffer->id))
  {
    yyerror("ast_scopedefn() failed - already defined id");
    return nullptr;
  }

  if (symbol_exists(buffer->id))
  {
    yyerror("ast_scopedefn() failed - already defined id");
    return nullptr;
  }

  symbol_insert(buffer->id, buffer->data);
  return buffer->data;
}

const char ast_scopedefn::get_stat_type() const
{
  return SCD_STAT_TYPE;
}

#endif
