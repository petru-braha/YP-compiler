#ifndef __0VARIABLEDATA0__
#define __0VARIABLEDATA0__

#include <string>
#include <string.h>
#include "dev/item_data.hpp"

const char *DATA_TYPE_INT = "int";
const char *DATA_TYPE_FLT = "float";
const char *DATA_TYPE_CHR = "char";
const char *DATA_TYPE_STR = "string";
const char *DATA_TYPE_BOL = "bool";
const char *RESERVED_TYPES[] =
    {DATA_TYPE_INT, DATA_TYPE_FLT,
     DATA_TYPE_CHR, DATA_TYPE_STR,
     DATA_TYPE_BOL};
constexpr unsigned char COUNT_RESERVED_TYPES = 5;

bool is_primitive(const std::string &type);
std::string default_value_of(const std::string &type);
std::string type_of(const std::string &primitive_value);

class function_data;
class object_data;
class symbol_table;

class variable_data final : public item_data
{
    std::string value;

    friend class function_data;
    friend class object_data;
    friend class symbol_table;
    variable_data(const variable_data &);

public:
    ~variable_data() = default;
    variable_data();
    variable_data(const std::string &);
    variable_data(const std::string &, const std::string &);
    variable_data(const std::string &, const variable_data &);

    variable_data &set_value(const std::string &);

    const std::string &get_value() const;
};

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
todo: has to reworked
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


#endif
