#ifndef __0VARIABLEDATA0__
#define __0VARIABLEDATA0__

#include <string>
#include <string.h>
#include "dev/symbol_data.hpp"
#include "dev/constexpr.hpp"
#include "dev/function.hpp"
#include "dev/yyerror.hpp"

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
