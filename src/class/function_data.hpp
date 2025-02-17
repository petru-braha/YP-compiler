#ifndef __0FUNCTIONDATA0__
#define __0FUNCTIONDATA0__

#include <string>
#include <vector>
#include <unordered_map>
#include "dev/symbol_data.hpp"
#include "dev/yyerror.hpp"

class ast_statement;
class ast_scope;

/* the parser makes heap allocations,
 * that are reverted in deconstructor here
 */
class function_data : public symbol_data
{
  const std::string return_data_type;

public:
  typedef std::unordered_map<
      std::string, mutable_data *>
      map;

private:
  map *parameters;

  std::vector<ast_statement *> *execution;

  static std::string available_id;
  const std::string &default_id();
  bool emplace(const std::vector<mutable_data *> *const);

public:
  virtual ~function_data() override;
  function_data(
      const std::string &, map *const);
  function_data(
      const std::string &, map *const,
      std::vector<ast_statement *> *const);
  bool define(std::vector<ast_statement *> *const);

  void *call(const std::vector<mutable_data *> *const);

  virtual const char get_item_type() const override;
  virtual const std::string &get_data_type() const override;
  const size_t get_count() const;
  const bool is_defined() const;

  typedef map::const_iterator it;
  it begin() const;
  it end() const;
};

std::string function_data::available_id = "";

const std::string &function_data::default_id()
{
  char character = 0;
  if ("" == available_id)
  {
    if (parameters->find(available_id) ==
        parameters->end())
      return available_id;
    available_id += character;
  }

  while (parameters->find(available_id) !=
         parameters->end())
  {
    character++;
    if (0 == character)
      available_id += character;
    size_t index_last = available_id.size() - 1;
    available_id[index_last] = character;
  }

  return available_id;
}

/*
 ! defined in ast_call.hpp
 * function_data::~function_data();
 */

// declaration with no definition
function_data::function_data(
    const std::string &return_type,
    std::unordered_map<
        std::string, mutable_data *> *const arguments)
    : return_data_type(return_type),
      parameters(arguments), execution(nullptr)
{
  if (nullptr == arguments)
    yyerror("function_data() failed - received nullptr");
}

// todo check compatibility
function_data::function_data(
    const std::string &return_type,
    std::unordered_map<
        std::string, mutable_data *> *const arguments,
    std::vector<ast_statement *> *const statements)
    : return_data_type(return_type),
      parameters(arguments), execution(statements)
{
  if (nullptr == arguments || nullptr == statements)
    yyerror("function_data() failed - received nullptr");
}

bool function_data::define(
    std::vector<ast_statement *> *const statements)
{
  if (execution)
    return false;
  execution = statements;
  return true;
}

/*
 ! defined in node.hpp after ast_scope
 * mutable_data *function_data::call(
    const std::vector<mutable_data *> &arguments);
 */

const char function_data::get_item_type() const
{
  return FNCT_SYMB_TYPE;
}

const std::string &function_data::get_data_type() const
{
  return return_data_type;
}

const size_t function_data::get_count() const
{
  return parameters->size();
}

function_data::it function_data::begin() const
{
  return parameters->begin();
}

function_data::it function_data::end() const
{
  return parameters->end();
}

const bool function_data::is_defined() const
{
  return nullptr == execution;
}

#endif
