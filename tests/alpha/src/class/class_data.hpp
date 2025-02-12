#ifndef __0CLASS_DATA0__
#define __0CLASS_DATA0__

#include <string>
#include <unordered_map>
#include "dev/table.hpp"
#include "dev/item_data.hpp"
#include "dev/function.hpp"

constexpr char ACCS_MODF_PRIV = 0;
constexpr char ACCS_MODF_PUBL = 1;

struct field
{
  item_data *data;
  const char access_modifier;
};

class class_data : public table
{
  std::unordered_map<std::string, field> itm;

public:
  virtual ~class_data() override;
  class_data() = default;

  class_data &insert(
      const std::string &, item_data *const, const char);
  field *get_data(const std::string &);

  virtual const size_t get_count(const char) const override;

  typedef std::unordered_map<
      std::string, field>::iterator it;
  it begin();
  it end();
};

class_data::~class_data()
{
  for (const auto &item_pair : itm)
    delete item_pair.second.data;
}

/* makes a copy of the pointer */
class_data &class_data::
    insert(const std::string &id,
           item_data *const value,
           const char access = ACCS_MODF_PRIV)
{
  if (nullptr == value)
  {
    yyerror("class_data.insert() failed - received nullptr");
    return *this;
  }

  std::pair<std::string, field>
      i_pair(id, {value, access});
  itm.insert(i_pair);
  return *this;
}

/* used for type_table too
the only time when we don't check for previous scopes too
 */
field *class_data::get_data(const std::string &id)
{
  auto it = itm.find(id);
  return it != itm.end() ? &((*it).second) : nullptr;
}

// see "dev/table.hpp" for the predefined value of item_type
const size_t class_data::get_count(const char item_type) const
{
  if (ITEM_TYPE_INVALID >= item_type)
    return itm.size();

  size_t count = 0;
  for (const auto &instance : itm)
    if (item_type ==
        instance.second.data->get_item_type())
      count++;
  return count;
}

class_data::it class_data::begin()
{
  return itm.begin();
}

class_data::it class_data::end()
{
  return itm.end();
}

#endif
