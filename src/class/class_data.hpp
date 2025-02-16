#ifndef __0CLASS_DATA0__
#define __0CLASS_DATA0__

#include <string>
#include <unordered_map>
#include "dev/symbol_data.hpp"
#include "dev/function.hpp"

constexpr char ACCS_MODF_PRIV = 0;
constexpr char ACCS_MODF_PUBL = 1;

struct field_data
{
  symbol_data *data;
  const char access_modifier;
};

// uses multimap -> multiple constructors
class class_data
{
  typedef std::unordered_multimap<
      std::string, field_data>
      map;
  map *content;

public:
  ~class_data();
  class_data();
  class_data(map *const);
  bool define(map *const);

  const size_t get_count(const char = SYMB_TYPE_INVALID) const;

  typedef map::iterator it;
  std::pair<it, it> get_data(const std::string &id);
  it begin();
  it end();
};

class_data::~class_data()
{
  if (nullptr == content)
    return;

  for (const auto &item_pair : *content)
    delete item_pair.second.data;
  delete content;
}

// declaration with no definition
class_data::class_data() : content(nullptr) {}

class_data::class_data(
    std::unordered_multimap<std::string, field_data> *const data)
    : content(data)
{
  if (nullptr == data)
    yyerror("class_data() failed - received nullptr");
}

bool class_data::define(map *const data)
{
  if (content)
    return false;
  content = data;
  return true;
}

std::pair<class_data::it, class_data::it> class_data::get_data(
    const std::string &id)
{
  return content->equal_range(id);
}

const size_t class_data::get_count(const char item_type) const
{
  if (SYMB_TYPE_INVALID >= item_type)
    return content->size();

  size_t count = 0;
  for (const auto &instance : *content)
    if (item_type ==
        instance.second.data->get_item_type())
      count++;
  return count;
}

class_data::it class_data::begin()
{
  return content->begin();
}

class_data::it class_data::end()
{
  return content->end();
}

#endif
