#ifndef __0STYP0__
#define __0STYP0__

#include <iostream>
#include <map>
#include <string>
#include <utility>

#include "synopsis.hpp"
#include "instance_data.hpp"
#include "type_data.hpp"

class type_table
{
    std::map<std::string, type_data> ids;

public:
    ~type_table();

    void add(const char *, std::string *, int);

    bool exists(const char *) const;
    void print() const;
};

type_table::~type_table()
{
    ids.clear();
}

//------------------------------------------------
// constant methods:

void type_table::add(const char *name, std::string *type, int line)
{
    ids [name] = type_data(type, line);
}

//------------------------------------------------
// constant methods:

bool type_table::exists(const char *name) const
{
    return ids.find(name) != ids.end();
}


#endif
