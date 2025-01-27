#ifndef __0TYPETABLE0__
#define __0TYPETABLE0__

#include <string>
#include <unordered_map>
#include "symbol_table.hpp"

std::unordered_map<std::string, symbol_table> type_table;

bool type_insert(const std::string &, const symbol_table &);
symbol_table *type_exists(const std::string &);

bool type_insert(const std::string &id,
                 const symbol_table &s)
{
    if (type_table.find(id) != type_table.end())
    {
        yyerror("class already defined");
        return false;
    }

    std::pair<std::string, symbol_table>
        s_pair(id, s);
    type_table.insert(s_pair);
    return true;
}

// DOES NOT provide error messages
symbol_table *type_exists(const std::string &id)
{
    if (type_table.find(id) != type_table.end())
        return &type_table.at(id);
    return nullptr;
}

#endif
