#ifndef __0CONSTANT0__
#define __0CONSTANT0__

#include <string>

class symbol_data;
class ast_expression;

extern int yylex();
void yywarning(const char *);
void yyerror(const char *);

bool make_copy(symbol_data *const, const symbol_data *const);

bool is_type(const std::string &);
bool is_compatible(const char *, const char *);
bool is_returning_char(ast_expression *const);

void *type_of(const char *const, const char);
void *print_f(const char *const, const char);
// no need of master

#endif
