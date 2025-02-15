#ifndef __0VARARRAYDATA0__
#define __0VARARRAYDATA0__

#include <vector>
#include <numeric>
#include "dev/yyerror.hpp"
#include "dev/symbol_data.hpp"
#include "dev/function.hpp"

#include "primitive_data.hpp"
#include "object_data.hpp"

std::string base_type(const std::string &);
void remove_level(std::string &data_type);

class array_data : public mutable_data
{
  // not const - changed by indexing
  std::string data_type;

  size_t index, level;
  const std::vector<size_t> level_data;

  std::vector<mutable_data *> m_array;

public:
  virtual ~array_data() override;
  array_data(const std::vector<size_t> &);
  array_data(
      const std::vector<size_t> &,
      mutable_data *const);
  array_data(
      const std::string &,
      const array_data &);

  array_data &operator=(const array_data &);

  // specific methods:
  void reset();
  void operator[](const size_t);
  mutable_data *get_value();

  // constant methods:
  virtual const char get_item_type() const override;
  virtual const std::string &get_data_type() const override;
};

//------------------------------------------------

std::string base_type(const std::string &array_type)
{
  size_t index = array_type.find('[');
  std::string result;
  result.append(array_type.c_str(), index);
  return result;
}

void remove_level(std::string &data_type)
{
  size_t index0 = data_type.find('[');
  if (std::string::npos == index0)
    return;

  size_t index1 = data_type.find(']', index0);
  if (std::string::npos == index1)
  {
    yyerror("remove_level() failed");
    return;
  }

  std::string::const_iterator it0, it1;
  it0 = data_type.begin() + index0;
  it1 = it0 + (index1 - index0 + 1);
  data_type.erase(it0, it1);
}

//------------------------------------------------

array_data::~array_data()
{
  for (size_t i = 0; i < m_array.size(); i++)
    delete m_array[i];
}

array_data::array_data(
    const std::vector<size_t> &level_data)
    : data_type(),
      index(0), level(0),
      level_data(level_data),
      m_array(std::accumulate(
          level_data.begin(), level_data.end(), 1,
          std::multiplies<size_t>()))
{
}

array_data::array_data(
    const std::vector<size_t> &level_data,
    mutable_data *const data)
    : data_type(),
      index(0), level(0),
      level_data(level_data),
      m_array()
{
  if (nullptr == data)
  {
    yyerror("array_data() failed - received nullptr");
    return;
  }

  m_array.reserve(std::accumulate(
      level_data.begin(), level_data.end(), 1,
      std::multiplies<size_t>()));
  m_array[0] = data;
  for (size_t i = 1; i < m_array.size(); i++)
    m_array[i] = make_copy(data);
}

array_data::array_data(
    const std::string &type,
    const array_data &data)
    : data_type(type),
      index(data.index), level(data.level),
      level_data(data.level_data),
      m_array(data.m_array.size())
{
  for (size_t i = 0; i < data.m_array.size(); i++)
    this->m_array[i] = make_copy(data.m_array[i]);
}

array_data &array_data::operator=(
    const array_data &data)
{
  
  return *this;
}

//------------------------------------------------

void array_data::reset()
{
  index = level = 0;
}

void array_data::operator[](const size_t idx)
{
  if (level >= level_data.size())
  {
    yyerror("array_data() failed - bad index");
    return;
  }

  if (idx >= level_data.at(level))
  {
    yyerror("array_data() failed - bad index");
    return;
  }

  size_t stride = std::accumulate(
      level_data.begin() + level + 1, level_data.end(), 1,
      std::multiplies<size_t>());
  stride *= idx;

  this->index += stride;
  level++;
}

mutable_data *array_data::get_value()
{
  return m_array[index];
}

//------------------------------------------------

const char array_data::get_item_type() const
{
  return ARRY_SYMB_TYPE;
}

const std::string &array_data::get_data_type() const
{
  return data_type;
}

#endif
