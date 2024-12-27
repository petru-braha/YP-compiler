#ifndef __0TYPETABLE0__
#define __0TYPETABLE0__

#include <map>
#include <string>
#include "symbol_table.hpp"

std::map<std::string, symbol_table> type_table;

bool type_insert(const std::string &, const symbol_table &);
const symbol_table *type_exists(const std::string &);

#endif
