#ifndef __0TYPETABLE0__
#define __0TYPETABLE0__

#include <string>
#include <unordered_map>
#include "class_data.hpp"

class type_table final
{
  static std::unordered_map<std::string, class_data *> content;

  ~type_table() = default;
  type_table() = delete;

  friend bool type_insert(
      const std::string &, class_data *const);
  friend class_data *type_exists(const std::string &);
};

std::unordered_map<
    std::string, class_data *>
    type_table::content;

bool type_insert(const std::string &id,
                 class_data *const s)
{
  if (type_table::content.find(id) !=
      type_table::content.end())
    return false;

  std::pair<std::string, class_data *>
      s_pair(id, s);
  type_table::content.insert(s_pair);
  return true;
}

class_data *type_exists(const std::string &id)
{
  if (type_table::content.find(id) != type_table::content.end())
    return type_table::content.at(id);
  return nullptr;
}

#endif
