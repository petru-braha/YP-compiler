#ifndef __0VARIABLEDATA0__
#define __0VARIABLEDATA0__

#include <string>
#include <string.h>
#include "dev/symbol_data.hpp"
#include "dev/yyerror.hpp"

const char INTG_DATA_TYPE[] = "int";
const char FLOT_DATA_TYPE[] = "float";
const char CHAR_DATA_TYPE[] = "char";
const char STRG_DATA_TYPE[] = "string";
const char BOOL_DATA_TYPE[] = "bool";
const char *RESERVED_TYPES[] =
    {INTG_DATA_TYPE, FLOT_DATA_TYPE,
     CHAR_DATA_TYPE, STRG_DATA_TYPE,
     BOOL_DATA_TYPE};
constexpr char COUNT_RESERVED_TYPES = 5;

bool is_primitive(const std::string &);
std::string default_value_of(const std::string &);
std::string type_of(const std::string &);

class primitive_data : public mutable_data
{
  const std::string data_type;
  std::string value;

public:
  virtual ~primitive_data() override = default;
  primitive_data(const std::string &);
  primitive_data(const std::string &, const std::string &);
  primitive_data(const std::string &, const primitive_data &);

  primitive_data &operator=(const primitive_data &);
  primitive_data &set_value(const std::string &);

  virtual const char get_item_type() const override;
  virtual const std::string &get_data_type() const override;
  const std::string &get_value() const;
};

//------------------------------------------------

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
  if (std::string(INTG_DATA_TYPE) == type)
    return "0";
  if (std::string(FLOT_DATA_TYPE) == type)
    return "0.0";
  if (std::string(CHAR_DATA_TYPE) == type)
    return "\'0\'";
  if (std::string(STRG_DATA_TYPE) == type)
    return "\"\"";
  if (std::string(BOOL_DATA_TYPE) == type)
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
      return INTG_DATA_TYPE;
    return FLOT_DATA_TYPE;
  case '\'':
    return CHAR_DATA_TYPE;
  case '\"':
    return STRG_DATA_TYPE;
  case 't':
    return BOOL_DATA_TYPE;
  case 'f':
    return BOOL_DATA_TYPE;
  }
}

//------------------------------------------------

primitive_data::primitive_data(const std::string &type)
    : data_type(type)
{
  if (false == is_primitive(type))
    yyerror("the argument should be primitive");
  this->value = default_value_of(type);
}

primitive_data::primitive_data(
    const std::string &type, const std::string &v)
    : data_type(type)
{
  if (false == is_primitive(type))
    yyerror("the argument should be primitive");
  if (type != type_of(v))
    yyerror("incompatible types");
  this->value = v;
}

// not verification required - v can only be legitimate
primitive_data ::primitive_data(
    const std::string &type, const primitive_data &v)
    : data_type(type), value(v.get_value())
{
  if (type != v.get_data_type())
  {
    yyerror("incompatible types");
    value = default_value_of(type);
  }
}

primitive_data &primitive_data::operator=(const primitive_data &p)
{
  if (data_type != p.data_type)
  {
    yyerror("primitive assignation failed - type missmatch");
    return *this;
  }

  value = p.value;
  return *this;
}

primitive_data &primitive_data::set_value(const std::string &value)
{
  if (this->get_data_type() != type_of(value))
    yyerror("incompatible types");
  this->value = value;
  return *this;
}

const char primitive_data::get_item_type() const
{
  return PRMT_SYMB_TYPE;
}

const std::string &primitive_data::get_data_type() const
{
  return data_type;
}

const std::string &primitive_data::get_value() const
{
  return value;
}

#endif
