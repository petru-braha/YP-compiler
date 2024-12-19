#ifndef __0TYPETABLE0__
#define __0TYPETABLE0__

#include <map>
#include "type_data.hpp"

std::map<const char *, type_data> type_table;

void type_add(const char* name)
{
    type_table.insert({name, type_data()});
}

bool type_exists(const char *name)
{
    return type_table.find(name) != type_table.end();
}

#endif
