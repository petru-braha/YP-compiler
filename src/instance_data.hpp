#ifndef __0INFO0__
#define __0INFO0__

#include <iostream>
#include <string>
#include "synopsis.hpp"

constexpr unsigned char ITEM_TYPE_VAR = 0;
constexpr unsigned char ITEM_TYPE_FCT = 1;
constexpr unsigned char ITEM_TYPE_CLS = 2;

constexpr char *DATA_TYPE_INT = "int";
constexpr char *DATA_TYPE_FLT = "float";
constexpr char *DATA_TYPE_CHR = "char";
constexpr char *DATA_TYPE_STR = "string";
constexpr char *DATA_TYPE_BOL = "bool";
constexpr char *RESERVED_TYPES[] =
    {DATA_TYPE_INT, DATA_TYPE_FLT,
     DATA_TYPE_CHR, DATA_TYPE_STR,
     DATA_TYPE_BOL};
constexpr unsigned char COUNT_RESERVED_TYPES = 5;

// id = name of the instance
class instance_data
{
    unsigned char item_type;
    std::string data_type, name;
    synopsis *instance_synopsis;

public:
    instance_data(const char *,
                  const char *,
                  const char *);

    unsigned char get_item_type() const;
    const char *get_data_type() const;
    const char *get_name() const;
};

//------------------------------------------------
// constructors:

instance_data::instance_data(const char *d_t,
                             const char *n,
                             const char *line)
    : item_type(ITEM_TYPE_VAR), data_type(d_t),
      name(n), instance_synopsis(nullptr)
{
    // verification
    if (nullptr == d_t || nullptr == n)
    {
        std::cout
            << "error - instance_data: wrong parameters.\n:";
        throw -1;
    }

    // define item_type
    bool reserved = false;
    for (size_t i = 0; i < COUNT_RESERVED_TYPES; i++)
        if (data_type.find(RESERVED_TYPES[i]))
        {
            reserved = true;
            break;
        }

    if (nullptr == line) // not a f
    {
        if (false == reserved)
            item_type = ITEM_TYPE_CLS;
    }
    else
    {
        if (std::string::npos ==
            data_type.find("(")) // not a f
            if (false == reserved)
                item_type = ITEM_TYPE_CLS;
        item_type = ITEM_TYPE_FCT;
    }

    // define synopsis
    switch (item_type)
    {
    case ITEM_TYPE_VAR:
        this->instance_synopsis =
            new synopsis_variable(line);
        break;
    case ITEM_TYPE_FCT:
        this->instance_synopsis =
            new synopsis_function(line);
        break;
    case ITEM_TYPE_CLS:
        this->instance_synopsis =
            new synopsis_class(line);
        break;

    default:
        std::cout << "error - instance data: wrong item type.\n";
        break;
    }
}

//------------------------------------------------
// constant methods:

#endif
