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
    ~symbol_table();
    symbol_table();
    symbol_table(const std::string &);

    symbol_table &insert(const std::string &,
                         item_data *const);

    item_data *get_data(const std::string &) const;
    const size_t get_count() const;
    const size_t get_count_variable() const;
    const size_t get_count_function() const;
    const size_t get_count_object() const;
    const std::string &get_id() const;

    typedef std::unordered_map<
        std::string, item_data *>::iterator it;
    it begin();
    it end();
};

size_t symbol_table::available_id = 0;

symbol_table::~symbol_table()
{
    for (const auto &item_pair : itm)
    {
        item_data *i = item_pair.second;
        if (nullptr == i)
            continue;

        if (ITEM_TYPE_VAR ==
            i->get_item_type())
        {
            variable_data *v = (variable_data *)i;
            delete v;
            continue;
        }

        if (ITEM_TYPE_FCT ==
            i->get_item_type())
        {
            function_data *f = (function_data *)i;
            delete f;
            continue;
        }

        if (ITEM_TYPE_OBJ ==
            i->get_item_type())
        {
            object_data *o = (object_data *)i;
            delete o;
        }
    }
}

symbol_table::symbol_table()
    : s_id(std::to_string(available_id))
{
    available_id++;
}

symbol_table::symbol_table(const std::string &s_id)
    : s_id(s_id) {}

/* makes a copy of the pointer */
symbol_table &symbol_table::
    insert(const std::string &id,
           item_data *const value)
{
    if (nullptr == value)
    {
        yyerror("invalid parameter pointer");
        return *this;
    }

    if (ITEM_TYPE_VAR == value->get_item_type())
    {
        variable_data *v_data = (variable_data *)value;
        variable_data *to_insert =
            new variable_data(v_data->get_data_type(),
                              v_data->get_value());
        std::pair<std::string, item_data *>
            i_pair(id, to_insert);
        itm.insert(i_pair);
        return *this;
    }

    if (ITEM_TYPE_FCT == value->get_item_type())
    {
        function_data *f_data = (function_data *)value;
        function_data *to_insert = new function_data(*f_data);
        std::pair<std::string, item_data *>
            i_pair(id, to_insert);
        itm.insert(i_pair);
        return *this;
    }

    object_data *o_data = (object_data *)value;
    object_data *to_insert = new object_data(*o_data);
    std::pair<std::string, item_data *>
        i_pair(id, to_insert);
    itm.insert(i_pair);
    return *this;
}

/* used for type_table too
the only time when we don't check for previous scopes too
 */
item_data *symbol_table::get_data(const std::string &id) const
{
    if (itm.find(id) != itm.end())
        return (*itm.find(id)).second;
    return nullptr;
}

const std::string &symbol_table::get_id() const
{
    return s_id;
}

const size_t symbol_table::get_count() const
{
    return itm.size();
}

const size_t symbol_table::get_count_variable() const
{
    size_t count = 0;
    for (const auto &instance : itm)
        if (ITEM_TYPE_VAR ==
            instance.second->get_item_type())
            count++;
    return count;
}

const size_t symbol_table::get_count_function() const
{
    size_t count = 0;
    for (const auto &instance : itm)
        if (ITEM_TYPE_FCT ==
            instance.second->get_item_type())
            count++;
    return count;
}

const size_t symbol_table::get_count_object() const
{
    size_t count = 0;
    for (const auto &instance : itm)
        if (ITEM_TYPE_OBJ ==
            instance.second->get_item_type())
            count++;
    return count;
}

symbol_table::it symbol_table::begin()
{
    return itm.begin();
}

symbol_table::it symbol_table::end()
{
    return itm.end();
}

#endif
