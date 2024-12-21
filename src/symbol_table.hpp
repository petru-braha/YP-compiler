#ifndef __0SYMBOLTABLE0__
#define __0SYMBOLTABLE0__

#include <map>
#include <string>

#include "synopsis.hpp"
#include "instance_data.hpp"

class symbol_table
{
    std::map<std::string, instance_data> ids;

public:
    ~symbol_table() = default;
    symbol_table() = default;

    void add(const char *,
             const char *,
             const char *);
    const instance_data *exists(const char *) const;
};

void symbol_table::add(const char *name,
                       const char *type,
                       const char *line)
{
    instance_data data(type, line);
    ids.insert({std::string(name), data});
}

const instance_data *symbol_table::exists(const char *name) const
{
    if (ids.find(std::string(name)) != ids.end())
        return &ids.at(name);
    return nullptr;
}

#endif
