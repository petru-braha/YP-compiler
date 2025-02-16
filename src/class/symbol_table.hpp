#ifndef __0SYMBOLTABLE0__
#define __0SYMBOLTABLE0__

#include <string>
#include <unordered_map>
#include "dev/symbol_data.hpp"
#include "dev/function.hpp"

/* commments
 * exists method are useful just
 * already defnied identifiers have to be searched in all scopes
 * not in just one symbol table

 * exception: symbol table insertions won't provide error messages
 * refined symbol table: 112 bytes removed from each instance
    but time complexities won't suffer
 */
class symbol_table
{
  const std::string s_id;
  std::unordered_map<std::string, symbol_data *> itm;

  static size_t available_id;

public:
  ~symbol_table();
  symbol_table();
  symbol_table(const std::string &);

  symbol_table &insert(const std::string &,
                       symbol_data *const);

  const size_t get_count(const char = SYMB_TYPE_INVALID) const;
  const std::string &get_id() const;
  symbol_data *get_data(const std::string &) const;

  typedef std::unordered_map<
      std::string, symbol_data *>::iterator it;
  it begin();
  it end();
};

size_t symbol_table::available_id = 0;

symbol_table::~symbol_table()
{
  for (const auto &item_pair : itm)
    delete item_pair.second;
}

symbol_table::symbol_table()
    : s_id(std::to_string(available_id))
{
  available_id++;
}

symbol_table::symbol_table(const std::string &s_id)
    : s_id(s_id)
{
}

/* makes a copy of the pointer */
symbol_table &symbol_table::
    insert(const std::string &id,
           symbol_data *const value)
{
  if (nullptr == value)
  {
    yyerror("symbol_table.insert() failed - received nullptr");
    return *this;
  }

  std::pair<std::string, symbol_data *>
      i_pair(id, value);
  itm.insert(i_pair);
  return *this;
}

const size_t symbol_table::get_count(const char item_type) const
{
  if (SYMB_TYPE_INVALID >= item_type)
    return itm.size();

  size_t count = 0;
  for (const auto &instance : itm)
    if (item_type ==
        instance.second->get_item_type())
      count++;
  return count;
}

/* used for type_table too
the only time when we don't check for previous scopes too
 */
symbol_data *symbol_table::get_data(const std::string &id) const
{
  auto it = itm.find(id);
  return it != itm.end() ? (*it).second : nullptr;
}

const std::string &symbol_table::get_id() const
{
  return s_id;
}

symbol_table::it symbol_table::begin()
{
  return itm.begin();
}

symbol_table::it symbol_table::end()
{
  return itm.end();
}

#endif
