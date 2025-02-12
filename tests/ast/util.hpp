#ifndef __0UTILITY0__
#define __0UTILITY0__

#include "../../src/dev/yyerror.hpp"

/* comments
 * this file is responsable of the inclusion order
 * all classes find their implementation here

 * error messages are provided when foreign keys ask to be
    included in the current data
        constructors
        specific methods (such as insertions)
    interogations won't send any messages
    their data is already filtered
        constant methods
        iterator methods

 * object_data <- symbol_table <- type_table <- object_data

 * exception: symbol table insertions won't provide error messages
 */

void yyerror(const char *s);

#include "../../src/variable_data.hpp"
#include "../../src/function_data.hpp"
#include "../../src/object_data.hpp"
#include "../../src/symbol_table.hpp"
#include "../../src/type_table.hpp"

item_data::item_data(const unsigned char i_t,
                     const std::string &d_t)
    : item_type(i_t), data_type(d_t)
{
    if (i_t > ITEM_TYPE_OBJ)
        yyerror("wrong item type");
}

const unsigned char item_data::get_item_type() const
{
    return item_type;
}

const std::string &item_data::get_data_type() const
{
    return data_type;
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

/* for primitive types only
 */
std::string type_of(const std::string &primitive_value)
{
    switch (primitive_value.at(0))
    {
    default:
        if (primitive_value.find('.') == std::string::npos)
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

// private
variable_data::variable_data(const variable_data &v)
    : item_data(ITEM_TYPE_VAR, v.get_data_type()),
      value(v.get_value())
{
}

[[deprecated("not a safe method, always be specific")]]
variable_data::variable_data()
    : item_data(ITEM_TYPE_VAR, std::string(DATA_TYPE_INT))
{
}

variable_data::variable_data(const std::string &type)
    : item_data(ITEM_TYPE_VAR, type)
{
    if (false == is_primitive(type))
        yyerror("the argument should be primitive");
    this->value = default_value_of(type);
}

variable_data::variable_data(const std::string &type,
                             const std::string &v)
    : item_data(ITEM_TYPE_VAR, type), value()
{
    if (false == is_primitive(type))
        yyerror("the argument should be primitive");
    if (type != type_of(v))
        yyerror("incompatible types");
    this->value = v;
}

// not verification required - v can only be legitimate
variable_data ::variable_data(const std::string &type,
                              const variable_data &v)
    : item_data(ITEM_TYPE_VAR, type),
      value(v.get_value())
{
    if (type != v.get_data_type())
    {
        yyerror("incompatible types");
        value = default_value_of(type);
    }
}

variable_data &variable_data::set_value(const std::string &value)
{
    if (this->get_data_type() != type_of(value))
        yyerror("incompatible types");
    this->value = value;
    return *this;
}

const std::string &variable_data::get_value() const
{
    return value;
}

//!------------------------------------------------
//! function

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

//!------------------------------------------------
//! object

// private
object_data::object_data(const object_data &o)
    : item_data(ITEM_TYPE_OBJ, o.get_data_type())
{
}

object_data::~object_data()
{
    for (const auto &item_pair : attributes)
    {
        item_data *i = item_pair.second;
        if (ITEM_TYPE_VAR ==
            i->get_item_type())
        {
            variable_data *v = (variable_data *)i;
            // delete v;
            continue;
        }

        object_data *o = (object_data *)i;
        // delete o;
    }
}

[[deprecated("not a safe method, always be specific")]]
object_data::object_data()
    : item_data(ITEM_TYPE_OBJ, DATA_TYPE_INT)
{
}

// default values of fields are being set at compilation time
object_data::object_data(const std::string &type)
    : item_data(ITEM_TYPE_OBJ, type)
{
    if (is_primitive(type))
        yyerror("primitive type");
    symbol_table *s = type_exists(type);

    if (nullptr == s)
        ERR_UNDEF_TYPE;

    symbol_table o_attributes = *s;

    // initialization of data
    auto i = o_attributes.begin();
    while (i != o_attributes.end())
    {
        item_data *data = (*i).second;
        if (ITEM_TYPE_VAR == data->get_item_type())
        {
            std::pair<std::string, item_data *>
                i_pair((*i).first,
                       new variable_data(*((variable_data *)data)));
            attributes.insert(i_pair);
            i++;
            continue;
        }

        // it's pointless to copy function_data
        if (ITEM_TYPE_FCT == data->get_item_type())
        {
            i++;
            continue;
        }

        std::pair<std::string, item_data *>
            i_pair((*i).first,
                   new object_data(*((object_data *)data)));
        attributes.insert(i_pair);
        i++;
    }
}

/* why is this correct?
 * reach out to tests/extra/memory copy/f1()
 * used only by utility, not by parser
 */
object_data::object_data(const std::string &type,
                         const object_data &o)
    : item_data(ITEM_TYPE_OBJ, type),
      attributes(o.attributes)
{
    if (type != o.get_data_type())
    {
        yyerror("incompatible types");
        this->~object_data();
        *this = object_data(type);
    }
}

/* useful in initialization */
object_data &object_data::
    attribute_insert(const std::string &id,
                     item_data *const value)
{
    if (nullptr == value)
    {
        yyerror("invalid parameter pointer");
        return *this;
    }

    if (value->get_item_type() > ITEM_TYPE_OBJ)
        yyerror("bad news");
    if (ITEM_TYPE_FCT == value->get_item_type())
        yyerror("bad news");

    //  check if id belongs to type - redundant operation
    if (nullptr == type_exists(get_data_type())->get_data(id))
        yyerror("bad news");

    if (ITEM_TYPE_VAR == value->get_item_type())
    {
        variable_data *v_data = (variable_data *)value;
        variable_data *attribute = new variable_data(*v_data);
        std::pair<std::string, item_data *>
            o_pair(id, attribute);
        attributes.insert(o_pair);
        return *this;
    }

    object_data *o_data = (object_data *)value;
    object_data *attribute = new object_data(*o_data);
    std::pair<std::string, item_data *>
        o_pair(id, attribute);
    attributes.insert(o_pair);
    return *this;
}

/* useful in assignation */
object_data &object_data::
    set_attribute(const std::string &id,
                  item_data *const value)
{
    if (nullptr == value)
    {
        yyerror("invalid parameter pointer");
        return *this;
    }

    if (value->get_item_type() > ITEM_TYPE_OBJ)
        yyerror("bad news");
    if (ITEM_TYPE_FCT == value->get_item_type())
        yyerror("bad news");

    // check if id belongs to type
    if (nullptr == type_exists(get_data_type())->get_data(id))
        yyerror("bad news");

    if (value->get_data_type() !=
        attributes.at(id)->get_data_type())
        yyerror("incompatible types");

    if (ITEM_TYPE_VAR == value->get_item_type())
    {
        variable_data *v_data = (variable_data *)value;
        variable_data *attribute = new variable_data(*v_data);
        variable_data *old_attribute =
            (variable_data *)attributes.at(id);
        attributes[id] = attribute;
        delete old_attribute;
        return *this;
    }

    object_data *o_data = (object_data *)value;
    object_data *attribute = new object_data(*o_data);
    object_data *old_attribute =
        (object_data *)attributes.at(id);
    attributes[id] = attribute;
    delete old_attribute;
    return *this;
}

const size_t object_data::get_count_attributes() const
{
    return attributes.size();
}

item_data *object_data::
    get_attribute(const std::string &id) const
{
    return attributes.at(id);
}

object_data::it object_data::begin()
{
    return attributes.begin();
}

object_data::it object_data::end()
{
    return attributes.end();
}

//!------------------------------------------------
//!------------------------------------------------

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

//!------------------------------------------------
//!------------------------------------------------

bool type_insert(const std::string &id,
                 const symbol_table &s)
{
    if (type_table.find(id) != type_table.end())
    {
        yyerror("class already defined");
        return false;
    }

    std::pair<std::string, symbol_table>
        s_pair(id, s);
    type_table.insert(s_pair);
    return true;
}

// DOES NOT provide error messages
symbol_table *type_exists(const std::string &id)
{
    if (type_table.find(id) != type_table.end())
        return &type_table.at(id);
    return nullptr;
}

//!------------------------------------------------
//!------------------------------------------------
//! please remember that queries don't print errors

extern std::vector<symbol_table> symbols;
#define LAST_SCOPE symbols.size() - 1

/* goes through every scope
 * could add extra time complexity
 */
size_t scope_search(const std::string &id)
{
    return -1;
    for (size_t scope = LAST_SCOPE;; scope--)
    {
        if (symbols[scope].get_data(id))
            return scope;
        if (0 == scope)
            break;
    }

    return -1;
}

bool is_type(const std::string &id)
{
    return type_exists(id) || is_primitive(id);
}

/* a constant value can only be primitive */
bool is_compatible(const char *type, const char *constant_value)
{
    switch (constant_value[0])
    {
    default: // int
        if (nullptr == strchr(constant_value, '.'))
        {
            if (strcmp(type, DATA_TYPE_INT))
                return false;
        }

        // float
        if (strcmp(type, DATA_TYPE_FLT))
            return false;
        break;

    case '\'': // char
        if (strcmp(type, DATA_TYPE_CHR))
            return false;
        break;

    case 't': // bool
        if (strcmp(type, DATA_TYPE_BOL))
            return false;
        break;
    case 'f': // bool
        if (strcmp(type, DATA_TYPE_BOL))
            return false;
        break;

    case '\"': // string
        if (strcmp(type, DATA_TYPE_STR))
            return false;
        break;
    }

    return true;
}

#endif
