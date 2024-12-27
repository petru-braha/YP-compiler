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

bool is_primitive(const std::string &type)
{
    for (unsigned char i = 0; i < COUNT_RESERVED_TYPES; i++)
        if (0 == strcmp(RESERVED_TYPES[i], type.c_str()))
            return true;
    return false;
}

// should be used only for primitive types
std::string default_value_of(const std::string &type)
{
    if (0 == strcmp(DATA_TYPE_INT, type.c_str()))
        return "0";
    if (0 == strcmp(DATA_TYPE_FLT, type.c_str()))
        return "0.0";
    if (0 == strcmp(DATA_TYPE_CHR, type.c_str()))
        return "\'\'";
    if (0 == strcmp(DATA_TYPE_STR, type.c_str()))
        return "\"\"";
    if (0 == strcmp(DATA_TYPE_BOL, type.c_str()))
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

class variable_data final : public item_data
{
    std::string value;

public:
    ~variable_data() = default;
    variable_data(const std::string &);
    variable_data(const std::string &, const std::string &);
    variable_data(const variable_data&);

    variable_data &set_value(const std::string &);

    const std::string &get_value() const;
};

#endif
