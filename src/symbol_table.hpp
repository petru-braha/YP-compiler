#ifndef __0SYMBOLTABLE0__
#define __0SYMBOLTABLE0__

#include <string>
#include <unordered_map>
#include "variable_data.hpp"
#include "function_data.hpp"
#include "object_data.hpp"

/* commments
 * exists method are useful just
 * already defnied identifiers have to be searched in all scopes
 * not in just one symbol table

 * exception: symbol table insertions won't provide error messages
 * refined symbol table: 112 bytes removed from each instance
    but time complexities won't suffer
 */
class symbol_table
{
    std::string s_id;
    std::unordered_map<std::string, item_data *> itm;

    static size_t available_id;

public:
    ~symbol_table() = default;
    symbol_table();
    symbol_table(const std::string &);

    symbol_table &insert(const std::string &,
                         item_data *);

    item_data *get_data(const std::string &) const;
    size_t get_count() const;
    size_t get_count_variable() const;
    size_t get_count_function() const;
    size_t get_count_object() const;
    const std::string& get_id() const;
    
    typedef std::unordered_map<
        std::string, item_data *>::iterator itm_it;
    itm_it begin();
    itm_it end();
};

size_t symbol_table::available_id = 0;

#endif
