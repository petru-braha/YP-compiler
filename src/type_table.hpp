#ifndef __0TYPETABLE0__
#define __0TYPETABLE0__

#include <iostream>
#include <map>
#include <string>
#include <utility>

#include "type_data.hpp"

class type_table
{
    std::map<const char *, type_data> ids;

public:
    void add(const char *, std::string *, int);
    bool exists(const char *) const;
};

void type_table::add(const char *name,
                     std::string *type,
                     int line)
{
    type_data data(type, line);
    ids.insert({name, data});
}

//------------------------------------------------
// constant methods:

bool type_table::exists(const char *name) const
{
    return ids.find(name) != ids.end();
}

#endif
