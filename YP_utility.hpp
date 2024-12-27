#ifndef __0UTILITY0__
#define __0UTILITY0__

/* comments:
 * this file is responsable of the inclusion order
 * here, all classes find their implementation
 * type_table <- object_data <- symbol_table <- type_table <- object_data
 */

void yyerror(const char *s);

#include <src/variable_data.hpp>
#include <src/function_data.hpp>
#include <src/object_data.hpp>
#include <src/symbol_table.hpp>
#include <src/type_table.hpp>

/* why is it allowed?
 * this parent class only connects derived classes
 * the actual checkings are individual for both variable_data and object_data
 */
void item_data::set_item_type(const unsigned int i_t)
{
    if (i_t > ITEM_TYPE_OBJ)
        yyerror("item data initialization - wrong parameter");
    item_type = i_t;
}

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

const std::string &item_data::get_type() const
{
    return type;
}

//!------------------------------------------------
//! variable

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
    if (this->get_type() != type_of(value))
        yyerror("variable data initialization - not compatible types");
    this->value = value;
}

// not verification required - v can only be legitimate
variable_data ::variable_data(const variable_data &v)
    : item_data(ITEM_TYPE_VAR, v.get_type()), value(v.get_value()) {}

variable_data &variable_data::set_value(const std::string &value)
{
    if (this->get_type() != type_of(value))
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

function_data::~function_data()
{
    for (size_t i = 0; i < parameters.size(); i++)
        delete parameters[i];
    parameters.clear();
}

// no parameters
function_data::function_data(std::string &type)
    : return_type(type) {}

function_data::
    function_data(std::string &type,
                  const std::vector<item_data *> &param)
    : return_type(type), parameters()
{
    for (size_t i = 0; i < param.size(); i++)
    {
        item_data *data = param[i];
        if (ITEM_TYPE_VAR == data->get_item_type())
        {
            variable_data *v_data = static_cast<variable_data *>(data);
            variable_data *parameter = new variable_data(*v_data);
            parameters.emplace_back(parameter);
            continue;
        }

        object_data *o_data = static_cast<object_data *>(data);
        object_data *parameter = new object_data(*o_data);
        parameters.emplace_back(parameter);
    }
}

// to be called for every parameter - calling the function
function_data &function_data::
    set_parameter(const size_t index, item_data *const value)
{
    if (index > parameters.size())
        yyerror("function data setting - wrong index");
    if (value->get_type() != parameters.at(index)->get_type())
        yyerror("function data setting - type incompatiblity");

    if (ITEM_TYPE_VAR == value->get_item_type())
    {
        variable_data *v_data = static_cast<variable_data *>(value);
        variable_data *parameter = new variable_data(*v_data);
        item_data *old_parameter = parameters.at(index);
        parameters[index] = parameter;
        delete old_parameter;
        return *this;
    }

    object_data *o_data = static_cast<object_data *>(value);
    object_data *parameter = new object_data(*o_data);
    item_data *old_parameter = parameters.at(index);
    parameters[index] = parameter;
    delete old_parameter;
    return *this;
}

const std::string &function_data::get_return_type() const
{
    return return_type;
}

item_data *function_data::
    get_parameter(const size_t index) const
{
    if (index > parameters.size())
        yyerror("function data retrival - wrong index");
    return parameters.at(index);
}

//!------------------------------------------------
//! object

/* should be used only for NON-primitive types
 * recursive method
 */
void set_default_value(const object_data &);

object_data::object_data(std::string &type)
    : item_data(ITEM_TYPE_OBJ, type)
{
    if (is_primitive(type))
        yyerror("the type of an object can't be primitive");
}

object_data::
    object_data(std::string &type,
                const std::vector<item_data *> &attributes)
    : item_data(ITEM_TYPE_OBJ, type)
{
}

object_data &object_data::
    set_attribute(const size_t index, item_data *const att)
{
    if (index >= attributes.size())
        yyerror("object data setting - wrong index");

    attributes[index] = att;
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

symbol_table &symbol_table::
    variable_add(const std::string &name,
                 const variable_data &data)
{
    if (var.find(name) != var.end())
    {
        yyerror("variable already defined");
        return *this;
    }

    var.insert({name, data});
    return *this;
}

symbol_table &symbol_table::
    function_add(const std::string &name,
                 const function_data &data)
{
    if (fct.find(name) != fct.end())
    {
        yyerror("function already defined");
        return *this;
    }

    fct.insert({name, data});
    return *this;
}

symbol_table &symbol_table::
    object_add(const std::string &name,
               const object_data &data)
{
    if (obj.find(name) != obj.end())
    {
        yyerror("object already defined");
        return *this;
    }

    obj.insert({name, data});
    return *this;
}

variable_data *symbol_table::
    variable_exists(const std::string &name)
{
    if (var.find(name) != var.end())
        return &var[name];
    return nullptr;
}

function_data *symbol_table::
    function_exists(const std::string &name)
{
    if (fct.find(name) != fct.end())
        return &fct[name];
    return nullptr;
}

object_data *symbol_table::
    object_exists(const std::string &name)
{
    if (obj.find(name) != obj.end())
        return &obj[name];
    return nullptr;
}

//!------------------------------------------------
//!------------------------------------------------

bool type_insert(const std::string &name,
                 const symbol_table &s)
{
    if (type_table.find(name) != type_table.end())
    {
        yyerror("class already defined");
        return false;
    }

    type_table[name] = s;
    return true;
}

const symbol_table *type_exists(const std::string &name)
{
    if (type_table.find(name) != type_table.end())
        return &type_table.at(name);
    return nullptr;
}

#endif
