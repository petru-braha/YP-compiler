#ifndef __0SCOPESTACK0__
#define __0SCOPESTACK0__

#include <vector>
#include "symbol_table.hpp"

class scope_stack
{
  static std::vector<symbol_table> content;

public:
  ~scope_stack() = default;
  scope_stack() = delete;
  scope_stack(const scope_stack &) = delete;
  scope_stack(const scope_stack &&) = delete;

  static constexpr int INIT_SIZE = 1024;
  inline static size_t size() { return content.size(); }

  friend void scope_insert();
  friend void scope_remove();
  friend bool symbol_insert(const std::string &, symbol_data *const);
  friend symbol_data *symbol_exists(const std::string &);
};

std::vector<symbol_table> scope_stack::content;

void scope_insert()
{
  if (0 == scope_stack::content.size())
    scope_stack::content.reserve(scope_stack::INIT_SIZE);
  scope_stack::content.emplace_back();
}

void scope_remove()
{
  scope_stack::content.pop_back();
}

bool symbol_insert(const std::string &id,
                   symbol_data *const data)
{
  if (nullptr == data)
    return false;

  const size_t last_scope = scope_stack::content.size() - 1;
  if (last_scope == -1)
    return false;

  scope_stack::content.at(last_scope).insert(id, data);
  return true;
}

symbol_data *symbol_exists(const std::string &id)
{
  if (0 == scope_stack::size())
    return nullptr;

  const size_t last_scope = scope_stack::size() - 1;
  if (last_scope == -1)
    return nullptr;

  for (size_t scope = last_scope;; scope--)
  {
    symbol_data *data = scope_stack::content.at(scope).get_data(id);
    if (data)
      return data;
    if (0 == scope)
      break;
  }

  return nullptr;
}

#endif
