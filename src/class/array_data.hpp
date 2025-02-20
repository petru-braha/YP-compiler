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
bool remove_level(std::string &);

class array_data : public mutable_data
{
  std::string data_type;
  size_t index, level;
  std::vector<size_t> level_data;
  std::vector<mutable_data *> m_array;

  void init_data_type();

public:
  virtual ~array_data() override;
  array_data(const array_data &) = delete;
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
  size_t capacity() const;
  bool is_indexed() const;
};

void array_data::init_data_type()
{
  if (std::string::npos != data_type.find('['))
    return;
  if (index || level)
    return;
  if (0 == data_type.size())
    return;

  for (size_t i = 0; i < level_data.size(); i++)
  {
    data_type += '[';
    data_type += std::to_string(level_data.at(i));
    data_type += ']';
  }
}

array_data::~array_data()
{
  for (size_t i = 0; i < m_array.size(); i++)
    delete m_array[i];
}

array_data::array_data(
    const std::vector<size_t> &level_data,
    mutable_data *const data)
    : data_type(data->get_data_type()),
      index(0), level(0),
      level_data(level_data)
{
  if (nullptr == data)
  {
    yyerror("array_data() failed - received nullptr");
    return;
  }

  init_data_type();

  size_t n = std::accumulate(
      level_data.begin(), level_data.end(), 1,
      std::multiplies<size_t>());
  m_array.reserve(n);
  for (size_t i = 0; i < n; i++)
  {
    mutable_data *copy = nullptr;
    if (false == make_copy(copy, data))
      yyerror("make_copy() failed");
    m_array.emplace_back(copy);
  }
}

array_data::array_data(
    const std::string &type,
    const array_data &data)
    : data_type(data.data_type),
      index(0), level(0)
{
  for (size_t i = 0; i < data.level; i++)
    remove_level(this->data_type);

  size_t n = 1;
  size_t levels = data.level_data.size() - data.level;
  level_data.reserve(levels);

  for (size_t i = data.level;
       i < data.level_data.size(); i++)
  {
    level_data.emplace_back(data.level_data.at(i));
    n *= data.level_data.at(i);
  }

  m_array.reserve(n);
  for (size_t i = 0; i < n; i++)
  {
    mutable_data *copy = nullptr;
    if (false == make_copy(copy, data.m_array[data.index + i]))
    {
      yyerror("array_data() failed - make_copy() failed");
      return;
    }

    m_array.emplace_back(copy);
  }
}

array_data &array_data::operator=(
    const array_data &data)
{
  std::string type_left = data_type,
              type_rght = data.data_type;

  for (size_t i = 0; i < this->level; i++)
    remove_level(type_left);
  for (size_t i = 0; i < data.level; i++)
    remove_level(type_rght);

  const char
      refi_left = this->m_array[0]->get_item_type(),
      refi_rght = data.m_array[0]->get_item_type();
  const std::string
      &refd_left = this->m_array[0]->get_data_type(),
      &refd_rght = data.m_array[0]->get_data_type();

  if (type_left != type_rght ||
      refi_left != refi_rght ||
      refd_left != refd_rght)
  {
    yyerror("array_data assignation failed - "
            "type missmatch");
    return *this;
  }

  size_t count = capacity();
  for (size_t i = 0; i < count; i++)
  {
    size_t left = this->index + i,
           rght = data.index + i;
    delete m_array[left];
    m_array[left] = nullptr;
    if (false == make_copy(m_array[left], data.m_array[rght]))
    {
      yyerror("array_data assignation failed - "
              "type missmatch");
      return *this;
    }
  }

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
  if (is_indexed())
    return m_array[index];
  return this;
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

size_t array_data::capacity() const
{
  return std::accumulate(
      level_data.begin() + level, level_data.end(), 1,
      std::multiplies<size_t>());
}

bool array_data::is_indexed() const
{
  return level_data.size() == level;
}

//------------------------------------------------

std::string base_type(const std::string &array_type)
{
  size_t index = array_type.find('[');
  if (std::string::npos != index)
    return array_type.substr(0, index);
  return "";
}

bool remove_level(std::string &data_type)
{
  size_t index0 = data_type.find('[');
  if (std::string::npos == index0)
    return false;

  size_t index1 = data_type.find(']', index0);
  if (std::string::npos == index1)
  {
    yyerror("remove_level() failed");
    return false;
  }

  std::string::const_iterator it0, it1;
  it0 = data_type.begin() + index0;
  it1 = it0 + (index1 - index0 + 1);
  data_type.erase(it0, it1);
  return true;
}

#endif
