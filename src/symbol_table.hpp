#ifndef __0SYMBOLTABLE0__
#define __0SYMBOLTABLE0__

#include <map>
#include <string>

#include "synopsis.hpp"
#include "instance_data.hpp"

class symbol_table
{
    std::map<const char*, instance_data> ids;
    std::string scope;

public:
    ~symbol_table() = default;
    symbol_table() = delete;
    symbol_table(const char *);

    void add(const char *,
             const char *,
             const char *);
    bool exists(const char *) const;
};

symbol_table::symbol_table(const char *name)
    : ids(), scope(name) {}

void symbol_table::add(const char *name,
                       const char *type,
                       const char *line)
{
    instance_data data(type, line);
    ids.insert({name, data});
}

bool symbol_table::exists(const char *name) const
{
    return ids.find(name) != ids.end();
}

#endif
