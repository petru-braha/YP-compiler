#ifndef __0OBJECTDATA0__
#define __0OBJECTDATA0__

#include <unordered_map>
#include "dev/yyerror.hpp"
#include "dev/item_data.hpp"
#include "dev/function.hpp"
#include "class_data.hpp"
#include "type_table.hpp"

mutable_data *make_copy(const mutable_data *const data);
bool is_primitive(const std::string &);
std::string default_value_of(const std::string &);
std::string type_of(const std::string &);

/* the methods will be stored in the type table
 * every object_data instance will !!! NOT !!! first contain pointers to
    variable_data instances
    and then pointers to object_data instances
 * the pointer order should be directed by the class
 * iterator methods are required for initialization
 */
class object_data : public mutable_data
{
  const std::string data_type;

  typedef std::unordered_map<
      std::string, field_data>
      map;
  map *attributes;

public:
  virtual ~object_data() override;
  object_data(const std::string &);
  object_data(const std::string &, map *const);
  object_data(const std::string &, const object_data &);

  object_data &operator=(const object_data &);

  virtual const char get_item_type() const override;
  virtual const std::string &get_data_type() const override;
  field_data *get_attriubte(const std::string &id) const;

  typedef std::unordered_map<
      std::string, field_data>::iterator it;
  it begin();
  it end();
};

object_data::~object_data()
{
  for (const auto &item_pair : *attributes)
    delete item_pair.second.data;
  delete attributes;
}

// default values of field_datas are being set at compilation time
object_data::object_data(const std::string &type)
    : data_type(type)
{
  if (is_primitive(type))
    yyerror("object_data() failed - primitive type");

  class_data *s = type_exists(type);
  if (nullptr == s)
    yyerror("object_data() failed - undefined type");

  // initialization of data
  attributes = new map;
  for (const auto &symbol : *s)
  {
    if (FNCT_ITEM_TYPE ==
        symbol.second.data->get_item_type())
      continue;

    const char access =
        symbol.second.access_modifier;
    mutable_data *data = (mutable_data *)symbol.second.data;
    std::pair<std::string, field_data> p(
        symbol.first, {make_copy(data), access});
    attributes->insert(p);
  }
}

object_data::object_data(
    const std::string &type,
    std::unordered_map<
        std::string, field_data> *const arguments)
    : data_type(type), attributes(arguments)
{
  if (nullptr == arguments)
    yyerror("object_data() failed - received nullptr");
}

// todo check compatibility
object_data::object_data(
    const std::string &type, const object_data &o)
    : data_type(type),
      attributes(new map(*o.attributes))
{
  if (type != o.data_type)
  {
    yyerror("object_data() failed - incompatible types");
    this->~object_data();
  }

  // todo copy each attribute in particular
}

const char object_data::get_item_type() const
{
  return OBJT_ITEM_TYPE;
}

const std::string &object_data::get_data_type() const
{
  return data_type;
}

field_data *object_data::get_attriubte(const std::string &id) const
{
  auto it = attributes->find(id);
  if (it != attributes->end())
    return &(*it).second;

  // member function
  class_data *s = type_exists(id);
  return s->get_data(id);
}

object_data::it object_data::begin()
{
  return attributes->begin();
}

object_data::it object_data::end()
{
  return attributes->end();
}

#endif
