#ifndef __0CONSTANT0__
#define __0CONSTANT0__

#include <string>

void yyerror(const char *s);

class item_data;
class mutable_data;

item_data *scope_search(const std::string &);
mutable_data *make_copy(const mutable_data *const);

bool is_type(const std::string &);
bool is_compatible(const char *, const char *);

void *type_of(const char *const, const char);
void *print_f(const char *const, const char);
// no need of master

#endif
