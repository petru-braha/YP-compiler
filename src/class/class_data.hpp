#ifndef __0CLASS_DATA0__
#define __0CLASS_DATA0__

#include <string>
#include <unordered_map>
#include "dev/table.hpp"
#include "dev/item_data.hpp"
#include "dev/function.hpp"

constexpr char ACCS_MODF_PRIV = 0;
constexpr char ACCS_MODF_PUBL = 1;

struct field_data
{
  item_data *data;
  const char access_modifier;
};

class class_data : public table
{
  typedef std::unordered_map<
      std::string, field_data>
      map;
  map *const itm;

public:
  virtual ~class_data() override;
  class_data(map *const);

  class_data &insert(const std::string &, const field_data &);
  field_data *get_data(const std::string &id);

  virtual const size_t get_count(const char) const override;

  typedef std::unordered_map<
      std::string, field_data>::iterator it;
  it begin();
  it end();
};

class_data::~class_data()
{
  for (const auto &item_pair : *itm)
    delete item_pair.second.data;
}

class_data::class_data(
    std::unordered_map<std::string, field_data> *const data)
    : itm(data)
{
  if (nullptr == data)
    yyerror("class_data() failed - received nullptr");
}

/* used for type_table too
the only time when we don't check for previous scopes too
 */
field_data *class_data::get_data(const std::string &id)
{
  auto it = itm->find(id);
  return it != itm->end() ? &((*it).second) : nullptr;
}

// see "dev/table.hpp" for the predefined value of item_type
const size_t class_data::get_count(const char item_type) const
{
  if (ITEM_TYPE_INVALID >= item_type)
    return itm->size();

  size_t count = 0;
  for (const auto &instance : *itm)
    if (item_type ==
        instance.second.data->get_item_type())
      count++;
  return count;
}

class_data::it class_data::begin()
{
  return itm->begin();
}

class_data::it class_data::end()
{
  return itm->end();
}

#endif
