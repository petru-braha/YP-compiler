#ifndef __0SCOPE0__
#define __0SCOPE0__

/* comments:
 * nullptr => error occured
 * symbol_data memory removal is performed by tables
 * and not here

 * ast_scope_control returns the break/continue statements
 * ast_scope DOES NOT
 */

#include <vector>
#include "class/dev/ast.hpp"
#include "class/dev/yyerror.hpp"

#include "ast_action.hpp"

class ast_scope : public ast_statement
{
  std::vector<ast_statement *> *const statemets;
  char result;

public:
  virtual ~ast_scope() override;
  ast_scope(std::vector<ast_statement *> *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_scope::~ast_scope()
{
  if (nullptr == statemets)
    return;

  for (size_t i = 0; i < statemets->size(); i++)
    delete statemets->at(i);
  delete statemets;
}

ast_scope::ast_scope(
    std::vector<ast_statement *> *const s)
    : statemets(s)
{
  if (nullptr == s)
    yyerror("ast_scope() failed - received nullptr");

  for (size_t i = 0; i < s->size(); i++)
    if (nullptr == s->at(i))
      yyerror("ast_scope() failed - received nullptr");
}

void *ast_scope::evaluate()
{
  if (nullptr == statemets)
    return nullptr;
  if (0 == statemets->size())
  {
    result = ACT_NOTHING;
    return &result;
  }

  scope_insert();

  size_t n = statemets->size();
  void *buffer = nullptr;
  for (auto &statement : *statemets)
  {
    buffer = statement->evaluate();
    if (ACT_RETURN == *(char *)buffer)
      return buffer;
  }

  scope_remove();
  return buffer;
}

const char ast_scope::get_stat_type() const
{
  return SCP_STAT_TYPE;
}

class ast_scope_control : public ast_statement
{
  std::vector<ast_statement *> *const statemets;
  char result;

public:
  virtual ~ast_scope_control() override;
  ast_scope_control(std::vector<ast_statement *> *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_scope_control::~ast_scope_control()
{
  if (nullptr == statemets)
    return;

  for (size_t i = 0; i < statemets->size(); i++)
    delete statemets->at(i);
  delete statemets;
}

ast_scope_control::ast_scope_control(
    std::vector<ast_statement *> *const s)
    : statemets(s)
{
  if (nullptr == s)
    yyerror("ast_scope_control() failed - received nullptr");

  for (size_t i = 0; i < s->size(); i++)
    if (nullptr == s->at(i))
      yyerror("ast_scope_control() failed - received nullptr");
}

void *ast_scope_control::evaluate()
{
  if (nullptr == statemets)
    return nullptr;
  if (0 == statemets->size())
  {
    result = ACT_NOTHING;
    return &result;
  }

  scope_insert();

  size_t n = statemets->size();
  void *buffer = nullptr;
  for (auto &statement : *statemets)
  {
    buffer = statement->evaluate();
    if (ACT_BREAK == *(char *)buffer ||
        ACT_CONTINUE == *(char *)buffer ||
        ACT_RETURN == *(char *)buffer)
      return buffer;
  }

  scope_remove();
  return buffer;
}

const char ast_scope_control::get_stat_type() const
{
  return SCC_STAT_TYPE;
}

#endif
