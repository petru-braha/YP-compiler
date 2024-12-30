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

class variable_data final : public item_data
{
    std::string value;

public:
    ~variable_data() = default;
    variable_data() : item_data(0, std::string(0)) {}
    variable_data(const std::string &);
    variable_data(const std::string &, const std::string &);
    variable_data(const variable_data &);

    variable_data &set_value(const std::string &);

    const std::string &get_value() const;
};

#endif
