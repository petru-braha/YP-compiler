#ifndef __0INFO0__
#define __0INFO0__

#include <iostream>
#include <string>
#include "synopsis.hpp"

constexpr unsigned char ITEM_TYPE_VAR = 0;
constexpr unsigned char ITEM_TYPE_FCT = 1;
constexpr unsigned char ITEM_TYPE_OBJ = 2;

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

// id = name of the instance
class instance_data
{
    unsigned char item_type;
    std::string data_type;
    synopsis *instance_synopsis;

public:
    instance_data();
    instance_data(const char *,
                  const char *);

    unsigned char get_item_type() const;
    const char *get_data_type() const;
};

//------------------------------------------------
// constructors:

instance_data::instance_data(const char *d_t,
                             const char *line)
    : item_type(ITEM_TYPE_VAR), data_type(d_t),
      instance_synopsis(nullptr)
{
    // verification
    if (nullptr == d_t)
    {
        std::cout
            << "error - instance_data: wrong parameters.\n:";
        throw -1;
    }

    // define item_type
    bool reserved = false;
    for (size_t i = 0; i < COUNT_RESERVED_TYPES; i++)
        if (data_type.find(RESERVED_TYPES[i]) != std::string::npos)
        {
            reserved = true;
            break;
        }

    if (nullptr == line) // not a f
    {
        if (false == reserved)
            item_type = ITEM_TYPE_OBJ;
    }
    else
    {
        if (std::string::npos ==
            data_type.find("(")) // not a f
            if (false == reserved)
                item_type = ITEM_TYPE_OBJ;
        item_type = ITEM_TYPE_FCT;
    }

    // define synopsis
    /*  switch (item_type)
      {
      case ITEM_TYPE_VAR: //
          this->instance_synopsis =
              new synopsis_variable(line);
          break;
      case ITEM_TYPE_FCT:
          this->instance_synopsis =
              new synopsis_function(line);
          break;
      case ITEM_TYPE_OBJ:
          this->instance_synopsis =
              new synopsis_class(line);
          break;

      default:
          std::cout << "error - instance data: wrong item type.\n";
          break;
      }*/
}

//------------------------------------------------
// constant methods:

unsigned char instance_data::get_item_type() const
{
    return item_type;
}

const char *instance_data::get_data_type() const
{
    return data_type.c_str();
}

#endif
