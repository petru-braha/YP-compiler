#ifndef __0SYMBOLTABLE0__
#define __0SYMBOLTABLE0__

#include <unordered_map>
#include <string>
#include "variable_data.hpp"
#include "function_data.hpp"
#include "object_data.hpp"

/* commments:
 * exists method are useful just
 * already defnied identifiers have to be searched in all scopes
 * not in just one symbol table
 */

class symbol_table
{
    // identifier => data
    std::unordered_map<std::string, variable_data> var;
    std::unordered_map<std::string, function_data> fct;
    std::unordered_map<std::string, object_data> obj;

public:
    ~symbol_table() = default;
    symbol_table() = default;

    symbol_table &variable_insert(const std::string &,
                                  const variable_data &);
    symbol_table &function_insert(const std::string &,
                                  const function_data &);
    symbol_table &object_insert(const std::string &,
                                const object_data &);

    variable_data *variable_exists(const std::string &);
    function_data *function_exists(const std::string &);
    object_data *object_exists(const std::string &);
    bool exists(const std::string &) const;

    size_t get_count_variable() const;
    size_t get_count_object() const;
    size_t get_count_declared() const;

    typedef std::unordered_map<
        std::string, variable_data>::iterator var_it;
    typedef std::unordered_map<
        std::string, object_data>::iterator obj_it;
    var_it variable_begin();
    var_it variable_end();
    obj_it object_begin();
    obj_it object_end();
};

#endif
