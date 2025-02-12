#ifndef __0VARIABLEDATA0__
#define __0VARIABLEDATA0__

#include <string>
#include <string.h>
#include "dev/item_data.hpp"

constexpr char *DATA_TYPE_INTG = "int";
constexpr char *DATA_TYPE_FLOT = "float";
constexpr char *DATA_TYPE_CHAR = "char";
constexpr char *DATA_TYPE_STRG = "string";
constexpr char *DATA_TYPE_BOOL = "bool";
constexpr char *RESERVED_TYPES[] =
    {DATA_TYPE_INTG, DATA_TYPE_FLOT,
     DATA_TYPE_CHAR, DATA_TYPE_STRG,
     DATA_TYPE_BOOL};
constexpr char COUNT_RESERVED_TYPES = 5;

bool is_primitive(const std::string &);
std::string default_value_of(const std::string &);
std::string type_of(const std::string &);

class primitive_data : public item_data
{
  std::string value;

public:
  ~primitive_data() = default;
  primitive_data(const std::string &);
  primitive_data(const std::string &, const std::string &);
  primitive_data(const std::string &, const primitive_data &);

  primitive_data &set_value(const std::string &);
  virtual item_data *operator[](const size_t);

  const std::string &get_value() const;
  virtual const char get_item_type() const;
  virtual const std::string &get_data_type() const;
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
  if (std::string(DATA_TYPE_INTG) == type)
    return "0";
  if (std::string(DATA_TYPE_FLOT) == type)
    return "0.0";
  if (std::string(DATA_TYPE_CHAR) == type)
    return "\'0\'";
  if (std::string(DATA_TYPE_STRG) == type)
    return "\"\"";
  if (std::string(DATA_TYPE_BOOL) == type)
    return "false";

  // not primitive
  return "";
}

std::string type_of(const std::string &primitive_value)
{
  switch (primitive_value.at(0))
  {
  default:
    if (primitive_value.find('.') == std::string::npos)
      return DATA_TYPE_INTG;
    return DATA_TYPE_FLOT;
  case '\'':
    return DATA_TYPE_CHAR;
  case '\"':
    return DATA_TYPE_STRG;
  case 't':
    return DATA_TYPE_BOOL;
  case 'f':
    return DATA_TYPE_BOOL;
  }
}

primitive_data::primitive_data(const std::string &type)
{
  if (false == is_primitive(type))
    yyerror("the argument should be primitive");
  this->value = default_value_of(type);
}

primitive_data::primitive_data(const std::string &type,
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
primitive_data ::primitive_data(const std::string &type,
                                const primitive_data &v)
    : item_data(ITEM_TYPE_VAR, type),
      value(v.get_value())
{
  if (type != v.get_data_type())
  {
    yyerror("incompatible types");
    value = default_value_of(type);
  }
}

primitive_data &primitive_data::set_value(const std::string &value)
{
  if (this->get_data_type() != type_of(value))
    yyerror("incompatible types");
  this->value = value;
  return *this;
}

const std::string &primitive_data::get_value() const
{
  return value;
}

#endif
