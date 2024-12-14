#ifndef __0SYMB0__
#define __0SYMB0__

#include <iostream>
#include <map>
#include <string>
#include <utility>

#include "synopsis.hpp"
#include "instance_data.hpp"

class symbol_table
{
    std::map<std::string, instance_data> ids;
    std::string scope;

public:
    ~symbol_table();
    symbol_table(const char *);

    void add(const char *, const char *, const char *);

    bool exists(const char *) const;
    void print() const;
};

//------------------------------------------------
// constructors:

symbol_table::~symbol_table()
{
    ids.clear();
}

symbol_table::symbol_table(const char *name) : scope(name) {}

//------------------------------------------------
// constant methods:

void symbol_table::add(const char *name, const char *type, const char *line)
{
    instance_data var(type, nullptr);
    ids[name] = var;
}

//------------------------------------------------
// constant methods:

bool symbol_table::exists(const char *name) const
{
    return ids.find(name) != ids.end();
}

void symbol_table::print() const
{
    for (const std::pair<std::string, instance_data> &v : ids)
        std::cout << "name: " << v.first << " type:" << v.second.get_data_type() << '\n';
}

#endif
