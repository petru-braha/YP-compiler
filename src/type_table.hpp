#ifndef __0TYPETABLE0__
#define __0TYPETABLE0__

#include <map>
#include <string>

std::map<std::string, symbol_table> type_table;

void type_insert(const std::string& name, symbol_table symbols)
{
    type_table.insert({name, symbol_table()});
}

const symbol_table *type_exists(const char *name)
{
    if (type_table.find(std::string(name)) != type_table.end())
        return &type_table.at(name);
    return nullptr;
}

#endif
