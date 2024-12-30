#ifndef __0TYPETABLE0__
#define __0TYPETABLE0__

#include <unordered_map>
#include <string>
#include "symbol_table.hpp"

extern std::unordered_map<std::string, symbol_table> type_table;

bool type_insert(const std::string &);
bool type_insert(const std::string &, const symbol_table &);
symbol_table *type_exists(const std::string &);

#endif
