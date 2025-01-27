#ifndef __0FUNCTIONDATA0__
#define __0FUNCTIONDATA0__

#include <string>
#include <unordered_map>
#include "dev/item_data.hpp"
#include "object_data.hpp"
#include "variable_data.hpp"

class symbol_table;

/* iterator methods required for function call */
class function_data final : public item_data
{
    std::unordered_map<
        std::string, item_data *>
        parameters;

    friend class object_data;
    friend class symbol_table;
    function_data(const function_data &);

    static std::string available_id;
    const std::string &default_id();

public:
    ~function_data();
    function_data();
    function_data(const std::string &);

    function_data &parameter_insert(item_data *const);
    function_data &parameter_insert(const std::string &,
                                    item_data *const);
    function_data &set_parameter(const std::string &,
                                 item_data *const);

    const size_t get_count_parameter() const;
    item_data *get_parameter(const std::string &) const;

    typedef std::unordered_map<
        std::string, item_data *>::iterator it;
    it begin();
    it end();
};

std::string function_data::available_id = "";

// private
function_data::function_data(const function_data &f)
    : item_data(ITEM_TYPE_FCT, f.get_data_type()),
      parameters(f.parameters)
{
}

const std::string &function_data::default_id()
{
    char character = 0;
    if ("" == available_id)
    {
        if (parameters.find(available_id) ==
            parameters.end())
            return available_id;
        available_id += character;
    }

    while (parameters.find(available_id) !=
           parameters.end())
    {
        character++;
        if (0 == character)
            available_id += character;
        size_t index_last = available_id.size() - 1;
        available_id[index_last] = character;
    }

    return available_id;
}

function_data::~function_data()
{
    for (const auto &item_pair : parameters)
    {
        item_data *i = item_pair.second;
        if (ITEM_TYPE_VAR ==
            i->get_item_type())
        {
            variable_data *v = (variable_data *)i;
            delete v;
            continue;
        }

        object_data *o = (object_data *)i;
        delete o;
    }
}

[[deprecated("not a safe method, always be specific")]]
function_data::function_data()
    : item_data(ITEM_TYPE_FCT, DATA_TYPE_INT)
{
}

// no parameters
function_data::function_data(const std::string &type)
    : item_data(ITEM_TYPE_FCT, type)
{
}

/* DOES NOT check for parameter definition */
function_data &function_data::
    parameter_insert(item_data *const value)
{
    if (nullptr == value)
    {
        yyerror("invalid parameter pointer");
        return *this;
    }

    // type checking
    if (value->get_item_type() > ITEM_TYPE_OBJ)
    {
        yyerror("bad news");
        return *this;
    }
    if (ITEM_TYPE_FCT == value->get_item_type())
    {
        yyerror("bad news");
        return *this;
    }

    if (ITEM_TYPE_VAR == value->get_item_type())
    {
        variable_data *v_data = (variable_data *)value;
        variable_data *parameter = new variable_data(*v_data);
        std::pair<std::string, item_data *>
            f_pair(default_id(), parameter);
        parameters.insert(f_pair);
        return *this;
    }

    object_data *o_data = (object_data *)value;
    object_data *parameter = new object_data(*o_data);
    std::pair<std::string, item_data *>
        f_pair(default_id(), parameter);
    parameters.insert(f_pair);
    return *this;
}

/* provides error messages
 * checks for parameter definition
 */
function_data &function_data::
    parameter_insert(const std::string &id,
                     item_data *const value)
{
    if (nullptr == value)
    {
        yyerror("invalid parameter pointer");
        return *this;
    }

    // type checking
    if (value->get_item_type() > ITEM_TYPE_OBJ)
    {
        yyerror("bad news");
        return *this;
    }
    if (ITEM_TYPE_FCT == value->get_item_type())
    {
        yyerror("bad news");
        return *this;
    }

    if (parameters.find(id) != parameters.end())
    {
        yyerror("parameter already defined");
        return *this;
    }

    if (value->get_item_type() > ITEM_TYPE_OBJ)
        yyerror("bad news");
    if (ITEM_TYPE_FCT == value->get_item_type())
        yyerror("bad news");

    if (ITEM_TYPE_VAR == value->get_item_type())
    {
        variable_data *v_data = (variable_data *)value;
        variable_data *parameter = new variable_data(*v_data);
        std::pair<std::string, item_data *>
            f_pair(id, parameter);
        parameters.insert(f_pair);
        return *this;
    }

    object_data *o_data = (object_data *)value;
    object_data *parameter = new object_data(*o_data);
    std::pair<std::string, item_data *>
        f_pair(id, parameter);
    parameters.insert(f_pair);
    return *this;
}

// to be called for every parameter - calling the function
function_data &function_data::
    set_parameter(const std::string &id,
                  item_data *const value)
{
    if (nullptr == value)
    {
        yyerror("invalid parameter pointer");
        return *this;
    }

    if (parameters.find(id) == parameters.end())
    {
        yyerror("parameter not found");
        return *this;
    }

    if (value->get_item_type() > ITEM_TYPE_OBJ)
        yyerror("bad news");
    if (ITEM_TYPE_FCT == value->get_item_type())
        yyerror("bad news");

    if (value->get_data_type() !=
        parameters.at(id)->get_data_type())
    {
        yyerror("incompatible types");
        return *this;
    }

    if (ITEM_TYPE_VAR == value->get_item_type())
    {
        variable_data *v_data = (variable_data *)value;
        variable_data *parameter = new variable_data(*v_data);
        variable_data *old_parameter =
            (variable_data *)parameters.at(id);
        std::pair<std::string, item_data *>
            f_pair(id, parameter);
        parameters.insert(f_pair);
        delete old_parameter;
        return *this;
    }

    object_data *o_data = (object_data *)value;
    object_data *parameter = new object_data(*o_data);
    object_data *old_parameter =
        (object_data *)parameters.at(id);
    std::pair<std::string, item_data *>
        f_pair(id, parameter);
    parameters.insert(f_pair);
    delete old_parameter;
    return *this;
}

const size_t function_data::get_count_parameter() const
{
    return parameters.size();
}

item_data *function_data::
    get_parameter(const std::string &id) const
{
    if (parameters.find(id) == parameters.end())
        yyerror("undefined paramater id");
    return parameters.at(id);
}

function_data::it function_data::begin()
{
    return parameters.begin();
}

function_data::it function_data::end()
{
    return parameters.end();
}


#endif
