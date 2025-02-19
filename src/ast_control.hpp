#ifndef __0ASTNODE0__
#define __0ASTNODE0__

/* comments:
 * nullptr => error occured
 * symbol_data memory removal is performed by tables
 * and not here
 */

#include "class/dev/ast.hpp"
#include "class/dev/yyerror.hpp"

class ast_scope_control;

class ast_ifelse : public ast_statement
{
  ast_expression *const judge;
  ast_scope_control *const sucss_case;
  ast_scope_control *const failr_case;

public:
  virtual ~ast_ifelse() override;
  ast_ifelse(ast_expression *const,
             ast_scope_control *const,
             ast_scope_control *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_ifelse::~ast_ifelse()
{
  delete judge;
  delete sucss_case;
  delete failr_case;
}

ast_ifelse::ast_ifelse(ast_expression *const j,
                       ast_scope_control *const s,
                       ast_scope_control *const f)
    : judge(j), sucss_case(s), failr_case(f)
{
  if (nullptr == judge ||
      nullptr == sucss_case ||
      nullptr == failr_case)
    yyerror("ast_ifelse() failed - received nullptr");
}

void *ast_ifelse::evaluate()
{
  const char *buffer = get_buffer(judge);

  if (0 == strcmp((char *)buffer, "true"))
    return sucss_case->evaluate();
  if (0 == strcmp((char *)buffer, "false"))
    return failr_case->evaluate();

  yyerror("ast_ifelse() failed - not primitive type");
  return nullptr;
}

const char ast_ifelse::get_stat_type() const
{
  return IFE_STAT_TYPE;
}

class ast_while : public ast_statement
{
  ast_expression *const judge;
  ast_scope_control *const sucss_case;

public:
  virtual ~ast_while() override;
  ast_while(ast_expression *const,
            ast_scope_control *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_while::~ast_while()
{
  delete judge;
  delete sucss_case;
}

ast_while::ast_while(ast_expression *const j,
                     ast_scope_control *const s)
    : judge(j), sucss_case(s)
{
  if (nullptr == judge || nullptr == sucss_case)
    yyerror("ast_while() failed - received nullptr");
}

void *ast_while::evaluate()
{
  const char *buffer = nullptr;
  void *data = nullptr;
  while (0 == strcmp(buffer = get_buffer(judge), "true"))
  {
    data = sucss_case->evaluate();
    const char byte = *(char *)data;
    if (ACT_BREAK == byte)
      break;
    else if (ACT_CONTINUE == byte)
      continue;
    else if (ACT_RETURN == byte)
      return data;
    else if (ACT_NOTHING == byte)
      ;
  }

  return data;
}

const char ast_while::get_stat_type() const
{
  return WHL_STAT_TYPE;
}

class ast_for : public ast_statement
{
  ast_statement *const initl;
  ast_expression *const judge;
  ast_expression *const incrm;
  ast_scope_control *const sucss_case;

public:
  virtual ~ast_for() override;
  ast_for(ast_statement *const,
          ast_expression *const,
          ast_expression *const,
          ast_scope_control *const);

  virtual void *evaluate() override;

  virtual const char get_stat_type() const override;
};

ast_for::~ast_for()
{
  delete initl;
  delete judge;
  delete incrm;
  delete sucss_case;
}

ast_for::ast_for(ast_statement *const iti,
                 ast_expression *const jdj,
                 ast_expression *const inc,
                 ast_scope_control *const s)
    : initl(iti), judge(jdj), incrm(inc), sucss_case(s)
{
  if (nullptr == iti || nullptr == jdj ||
      nullptr == inc || nullptr == s)
    yyerror("ast_for() failed - received nullptr");
}

void *ast_for::evaluate()
{
  scope_insert();
  initl->evaluate();

  void *data = nullptr;
  const char *buffer = get_buffer(judge);
  while (0 == strcmp(buffer, "true"))
  {
    data = sucss_case->evaluate();
    const char byte = *(char *)data;
    if (ACT_BREAK == byte)
      break;
    else if (ACT_CONTINUE == byte)
      continue;
    else if (ACT_RETURN == byte)
      return data;
    else if (ACT_NOTHING == byte)
      ;
    incrm->evaluate();
    buffer = get_buffer(judge);
  }

  scope_remove();
  return data;
}

const char ast_for::get_stat_type() const
{
  return FOR_STAT_TYPE;
}

#endif
