#ifndef __0UTILITY0__
#define __0UTILITY0__

/* comments:
 * this file is responsable of the inclusion order
 * here, all classes find their implementation
 * type_table <- object_data <- symbol_table <- type_table <- object_data
 */

void yyerror(const char *s);

#include "src/variable_data.hpp"
#include "src/function_data.hpp"
#include "src/object_data.hpp"
#include "src/symbol_table.hpp"
#include "src/type_table.hpp"

item_data::item_data(const unsigned char i_t,
                     const std::string &t)
    : item_type(i_t), type(t)
{
    if (i_t > ITEM_TYPE_OBJ)
        yyerror("item data initialization - wrong parameter");
}

const unsigned char item_data::get_item_type() const
{
    return item_type;
}

const std::string &item_data::get_data_type() const
{
    return type;
}

//!------------------------------------------------
//! variable

bool is_primitive(const std::string &type)
{
    for (unsigned char i = 0; i < COUNT_RESERVED_TYPES; i++)
        if (std::string(RESERVED_TYPES[i]) == type)
            return true;
    return false;
}

// should be used only for primitive types
std::string default_value_of(const std::string &type)
{
    if (std::string(DATA_TYPE_INT) == type)
        return "0";
    if (std::string(DATA_TYPE_FLT) == type)
        return "0.0";
    if (std::string(DATA_TYPE_CHR) == type)
        return "\'0\'";
    if (std::string(DATA_TYPE_STR) == type)
        return "\"\"";
    if (std::string(DATA_TYPE_BOL) == type)
        return "false";

    // not primitive
    return "";
}

std::string type_of(const std::string &primitive_value)
{
    switch (primitive_value.at(0))
    {
    default:
        if (primitive_value.find('.') != std::string::npos)
            return DATA_TYPE_INT;
        return DATA_TYPE_FLT;
    case '\'':
        return DATA_TYPE_CHR;
    case '\"':
        return DATA_TYPE_STR;
    case 't':
        return DATA_TYPE_BOL;
    case 'f':
        return DATA_TYPE_BOL;
    }
}

variable_data::variable_data(const std::string &type)
    : item_data(ITEM_TYPE_VAR, type)
{
    if (false == is_primitive(type))
        yyerror("variable data initialization - not primitive type");
    value = default_value_of(type);
}

variable_data::variable_data(const std::string &type,
                             const std::string &value)
    : item_data(ITEM_TYPE_VAR, type)
{
    if (false == is_primitive(type))
        yyerror("variable data initialization - not primitive type");
    if (this->get_data_type() != type_of(value))
        yyerror("variable data initialization - not compatible types");
    this->value = value;
}

// not verification required - v can only be legitimate
variable_data ::variable_data(const variable_data &v)
    : item_data(ITEM_TYPE_VAR, v.get_data_type()), value(v.get_value()) {}

variable_data &variable_data::set_value(const std::string &value)
{
    if (this->get_data_type() != type_of(value))
        yyerror("variable data initialization - not compatible types");
    this->value = value;
    return *this;
}

const std::string &variable_data::get_value() const
{
    return value;
}

//!------------------------------------------------
//! function

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
    for (auto parameter : parameters)
        delete parameter.second;
}

// no parameters
function_data::function_data(std::string &type)
    : return_type(type) {}

/* DOES NOT provide error messages
 * DOES NOT check for parameter definition
 */
function_data &function_data::
    parameter_insert(item_data *value)
{
    if (ITEM_TYPE_VAR == value->get_item_type())
    {
        variable_data *v_data = (variable_data *)value;
        variable_data *parameter = new variable_data(*v_data);
        parameters[default_id()] = parameter;
        return *this;
    }

    object_data *o_data = (object_data *)value;
    object_data *parameter = new object_data(*o_data);
    parameters[default_id()] = parameter;
    return *this;
}

/* provides error messages
 * checks for parameter definition
 */
function_data &function_data::
    parameter_insert(const std::string &id, item_data *value)
{
    if (parameters.find(id) != parameters.end())
    {
        yyerror("parameter already defined");
        return *this;
    }

    if (ITEM_TYPE_VAR == value->get_item_type())
    {
        variable_data *v_data = (variable_data *)value;
        variable_data *parameter = new variable_data(*v_data);
        parameters[id] = parameter;
        return *this;
    }

    object_data *o_data = (object_data *)value;
    object_data *parameter = new object_data(*o_data);
    parameters[id] = parameter;
    return *this;
}

// to be called for every parameter - calling the function
function_data &function_data::
    set_parameter(const std::string &id, item_data *value)
{
    if (parameters.find(id) == parameters.end())
    {
        yyerror("parameter not found");
        return *this;
    }

    if (value->get_data_type() !=
        parameters.at(id)->get_data_type())
    {
        yyerror("function data setting - type incompatiblity");
        return *this;
    }

    if (ITEM_TYPE_VAR == value->get_item_type())
    {
        variable_data *v_data = (variable_data *)value;
        variable_data *parameter = new variable_data(*v_data);
        variable_data *old_parameter =
            (variable_data *)parameters.at(id);
        parameters[id] = parameter;
        delete old_parameter;
        return *this;
    }

    object_data *o_data = (object_data *)value;
    object_data *parameter = new object_data(*o_data);
    object_data *old_parameter =
        (object_data *)parameters.at(id);
    parameters[id] = parameter;
    delete old_parameter;
    return *this;
}

const std::string &function_data::get_return_type() const
{
    return return_type;
}

size_t function_data::get_count_parameter() const
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

//!------------------------------------------------
//! object

object_data::~object_data()
{
    for (size_t i = 0; i < attributes.size(); i++)
        delete attributes[i];
    attributes.clear();
}

// default values of fields are being set at compilation time
object_data::object_data(std::string &type)
    : item_data(ITEM_TYPE_OBJ, type)
{
    if (is_primitive(type))
        yyerror("primitive type");
    symbol_table *s = type_exists(type);
    if (nullptr == s)
        yyerror("non-defined type");

    symbol_table o_attributes = *s;

    // initialization of data
    auto v = o_attributes.variable_begin();
    while (v != o_attributes.variable_end())
    {
        attributes.emplace_back(
            new variable_data((*v).second));
        v++;
    }

    auto o = o_attributes.object_begin();
    while (o != o_attributes.object_end())
    {
        attributes.emplace_back(
            new object_data((*o).second));
        o++;
    }
}

object_data::object_data(const object_data &o)
    : item_data(ITEM_TYPE_OBJ, o.get_data_type()),
      attributes(o.get_count_attributes())
{
    for (size_t i = 0; i < o.get_count_attributes(); i++)
    {
        item_data *value = o.get_attribute(i);
        if (ITEM_TYPE_VAR == value->get_item_type())
        {
            variable_data *v_data = (variable_data *)value;
            variable_data *attribute = new variable_data(*v_data);
            attributes[i] = attribute;
            continue;
        }

        object_data *o_data = (object_data *)value;
        object_data *attribute = new object_data(*o_data);
        attributes[i] = attribute;
    }
}

object_data &object_data::
    set_attribute(const size_t index, item_data *value)
{
    if (index > attributes.size())
        yyerror("object data setting - wrong index");
    if (value->get_data_type() != attributes.at(index)->get_data_type())
        yyerror("object data setting - type incompatiblity");

    if (ITEM_TYPE_VAR == value->get_item_type())
    {
        variable_data *v_data = (variable_data *)value;
        variable_data *attribute = new variable_data(*v_data);
        variable_data *old_attribute =
            (variable_data *)attributes.at(index);
        attributes[index] = attribute;
        delete old_attribute;
        return *this;
    }

    object_data *o_data = (object_data *)value;
    object_data *attribute = new object_data(*o_data);
    object_data *old_attribute =
        (object_data *)attributes.at(index);
    attributes[index] = attribute;
    delete old_attribute;
    return *this;
}

item_data *object_data::
    get_attribute(const size_t index) const
{
    if (index >= attributes.size())
        yyerror("object data setting - wrong index");
    return this->attributes.at(index);
}

//!------------------------------------------------
//!------------------------------------------------

symbol_table::symbol_table()
    : s_id(std::to_string(available_id))
{
    available_id++;
}

symbol_table::symbol_table(const std::string &s_id)
    : s_id(s_id) {}

symbol_table &symbol_table::
    variable_insert(const std::string &id,
                    const variable_data &data)
{
    var.insert({id, data});
    return *this;
}

symbol_table &symbol_table::
    function_insert(const std::string &id,
                    const function_data &data)
{
    fct.insert({id, data});
    return *this;
}

symbol_table &symbol_table::
    object_insert(const std::string &id,
                  const object_data &data)
{
    obj.insert({id, data});
    return *this;
}

// doesn't provide error messages
variable_data *symbol_table::
    variable_exists(const std::string &id)
{
    if (var.find(id) != var.end())
        return &var[id];
    return nullptr;
}

// doesn't provide error messages
function_data *symbol_table::
    function_exists(const std::string &id)
{
    if (fct.find(id) != fct.end())
        return &fct[id];
    return nullptr;
}

// doesn't provide error messages
object_data *symbol_table::
    object_exists(const std::string &id)
{
    if (obj.find(id) != obj.end())
        return &obj[id];
    return nullptr;
}

/* used for type_table
the only time when we don't check for previous scopes too
 * doesn't provide error messages
 */
bool symbol_table::exists(const std::string &id) const
{
    if (var.find(id) != var.end())
        return true;
    if (fct.find(id) != fct.end())
        return true;
    if (obj.find(id) != obj.end())
        return true;
    return false;
}

size_t symbol_table::get_id() const
{
    return available_id - 1;
}

size_t symbol_table::get_count_variable() const
{
    return var.size();
}

size_t symbol_table::get_count_object() const
{
    return obj.size();
}

size_t symbol_table::get_count_declared() const
{
    return var.size() + fct.size() + obj.size();
}

symbol_table::var_it symbol_table::variable_begin()
{
    return var.begin();
}

symbol_table::var_it symbol_table::variable_end()
{
    return var.end();
}

symbol_table::obj_it symbol_table::object_begin()
{
    return obj.begin();
}

symbol_table::obj_it symbol_table::object_end()
{
    return obj.end();
}

//!------------------------------------------------
//!------------------------------------------------

bool type_insert(const std::string &id)
{
    if (type_table.find(id) != type_table.end())
    {
        yyerror("class already defined");
        return false;
    }

    type_table.insert({id, symbol_table()});
    return true;
}

bool type_insert(const std::string &id,
                 const symbol_table &s)
{
    if (type_table.find(id) != type_table.end())
    {
        yyerror("class already defined");
        return false;
    }

    type_table.insert({id, s});
    return true;
}

// DOES NOT provide error messages
symbol_table *type_exists(const std::string &id)
{
    if (type_table.find(id) != type_table.end())
        return &type_table.at(id);
    return nullptr;
}

#endif
