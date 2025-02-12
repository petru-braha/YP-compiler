#ifndef __0UTILITY0__
#define __0UTILITY0__

/* comments
 * this file is responsable of the inclusion order
 * all classes find their implementation here

 * error messages are provided when foreign keys ask to be
    included in the current data
        constructors
        specific methods (such as insertions)
    interogations won't send any messages
    their data is already filtered
        constant methods
        iterator methods

 * object_data <- symbol_table <- type_table <- object_data

 * exception: symbol table insertions won't provide error messages
 */

#include "class/dev/yyerror.hpp"
#include "class/dev/constant.hpp"

#include "class/variable_data.hpp"
#include "class/function_data.hpp"
#include "class/object_data.hpp"
#include "class/symbol_table.hpp"
#include "class/type_table.hpp"

//!------------------------------------------------
//! function

// private
function_data::function_data(const function_data &f)
    : item_data(ITEM_TYPE_FCT, f.get_data_type()),
      parameters(f.parameters)
{
}

const std::string &function_data::default_id()
{
  char character = 0;
  if ("" == available_id)
  {
    if (parameters.find(available_id) ==
        parameters.end())
      return available_id;
    available_id += character;
  }

  while (parameters.find(available_id) !=
         parameters.end())
  {
    character++;
    if (0 == character)
      available_id += character;
    size_t index_last = available_id.size() - 1;
    available_id[index_last] = character;
  }

  return available_id;
}

function_data::~function_data()
{
  for (const auto &item_pair : parameters)
  {
    item_data *i = item_pair.second;
    if (ITEM_TYPE_VAR ==
        i->get_item_type())
    {
      variable_data *v = (variable_data *)i;
      delete v;
      continue;
    }

    object_data *o = (object_data *)i;
    delete o;
  }
}

const size_t function_data::get_count_parameter() const
{
  return parameters.size();
}

item_data *function_data::
    get_parameter(const std::string &id) const
{
  if (parameters.find(id) == parameters.end())
    yyerror("undefined paramater id");
  return parameters.at(id);
}

function_data::it function_data::begin()
{
  return parameters.begin();
}

function_data::it function_data::end()
{
  return parameters.end();
}

//!------------------------------------------------
//! object

// private
object_data::object_data(const object_data &o)
    : item_data(ITEM_TYPE_OBJ, o.get_data_type())
{
}

object_data::~object_data()
{
  for (const auto &item_pair : attributes)
  {
    item_data *i = item_pair.second;
    if (ITEM_TYPE_VAR ==
        i->get_item_type())
    {
      variable_data *v = (variable_data *)i;
      // delete v;
      continue;
    }

    object_data *o = (object_data *)i;
    // delete o;
  }
}

[[deprecated("not a safe method, always be specific")]]
object_data::object_data()
    : item_data(ITEM_TYPE_OBJ, DATA_TYPE_INT)
{
}

// default values of fields are being set at compilation time
object_data::object_data(const std::string &type)
    : item_data(ITEM_TYPE_OBJ, type)
{
  if (is_primitive(type))
    yyerror("primitive type");
  symbol_table *s = type_exists(type);

  if (nullptr == s)
    ERR_UNDEF_TYPE;

  symbol_table o_attributes = *s;

  // initialization of data
  auto i = o_attributes.begin();
  while (i != o_attributes.end())
  {
    item_data *data = (*i).second;
    if (ITEM_TYPE_VAR == data->get_item_type())
    {
      std::pair<std::string, item_data *>
          i_pair((*i).first,
                 new variable_data(*((variable_data *)data)));
      attributes.insert(i_pair);
      i++;
      continue;
    }

    // it's pointless to copy function_data
    if (ITEM_TYPE_FCT == data->get_item_type())
    {
      i++;
      continue;
    }

    std::pair<std::string, item_data *>
        i_pair((*i).first,
               new object_data(*((object_data *)data)));
    attributes.insert(i_pair);
    i++;
  }
}

/* why is this correct?
 * reach out to tests/extra/memory copy/f1()
 * used only by utility, not by parser
 */
object_data::object_data(const std::string &type,
                         const object_data &o)
    : item_data(ITEM_TYPE_OBJ, type),
      attributes(o.attributes)
{
  if (type != o.get_data_type())
  {
    yyerror("incompatible types");
    this->~object_data();
    *this = object_data(type);
  }
}

/* useful in initialization */
object_data &object_data::
    attribute_insert(const std::string &id,
                     item_data *const value)
{
  if (nullptr == value)
  {
    yyerror("invalid parameter pointer");
    return *this;
  }

  if (value->get_item_type() > ITEM_TYPE_OBJ)
    yyerror("bad news");
  if (ITEM_TYPE_FCT == value->get_item_type())
    yyerror("bad news");

  //  check if id belongs to type - redundant operation
  if (nullptr == type_exists(get_data_type())->get_data(id))
    yyerror("bad news");

  if (ITEM_TYPE_VAR == value->get_item_type())
  {
    variable_data *v_data = (variable_data *)value;
    variable_data *attribute = new variable_data(*v_data);
    std::pair<std::string, item_data *>
        o_pair(id, attribute);
    attributes.insert(o_pair);
    return *this;
  }

  object_data *o_data = (object_data *)value;
  object_data *attribute = new object_data(*o_data);
  std::pair<std::string, item_data *>
      o_pair(id, attribute);
  attributes.insert(o_pair);
  return *this;
}

/* useful in assignation */
object_data &object_data::
    set_attribute(const std::string &id,
                  item_data *const value)
{
  if (nullptr == value)
  {
    yyerror("invalid parameter pointer");
    return *this;
  }

  if (value->get_item_type() > ITEM_TYPE_OBJ)
    yyerror("bad news");
  if (ITEM_TYPE_FCT == value->get_item_type())
    yyerror("bad news");

  // check if id belongs to type
  if (nullptr == type_exists(get_data_type())->get_data(id))
    yyerror("bad news");

  if (value->get_data_type() !=
      attributes.at(id)->get_data_type())
    yyerror("incompatible types");

  if (ITEM_TYPE_VAR == value->get_item_type())
  {
    variable_data *v_data = (variable_data *)value;
    variable_data *attribute = new variable_data(*v_data);
    variable_data *old_attribute =
        (variable_data *)attributes.at(id);
    attributes[id] = attribute;
    delete old_attribute;
    return *this;
  }

  object_data *o_data = (object_data *)value;
  object_data *attribute = new object_data(*o_data);
  object_data *old_attribute =
      (object_data *)attributes.at(id);
  attributes[id] = attribute;
  delete old_attribute;
  return *this;
}

const size_t object_data::get_count_attributes() const
{
  return attributes.size();
}

item_data *object_data::
    get_attribute(const std::string &id) const
{
  return attributes.at(id);
}

object_data::it object_data::begin()
{
  return attributes.begin();
}

object_data::it object_data::end()
{
  return attributes.end();
}

//!------------------------------------------------
//!------------------------------------------------

symbol_table::~symbol_table()
{
  for (const auto &item_pair : itm)
  {
    item_data *i = item_pair.second;
    if (nullptr == i)
      continue;

    if (ITEM_TYPE_VAR ==
        i->get_item_type())
    {
      variable_data *v = (variable_data *)i;
      delete v;
      continue;
    }

    if (ITEM_TYPE_FCT ==
        i->get_item_type())
    {
      function_data *f = (function_data *)i;
      delete f;
      continue;
    }

    if (ITEM_TYPE_OBJ ==
        i->get_item_type())
    {
      object_data *o = (object_data *)i;
      delete o;
    }
  }
}

symbol_table::symbol_table()
    : s_id(std::to_string(available_id))
{
  available_id++;
}

symbol_table::symbol_table(const std::string &s_id)
    : s_id(s_id) {}

/* makes a copy of the pointer */
symbol_table &symbol_table::
    insert(const std::string &id,
           item_data *const value)
{
  if (nullptr == value)
  {
    yyerror("invalid parameter pointer");
    return *this;
  }

  if (ITEM_TYPE_VAR == value->get_item_type())
  {
    variable_data *v_data = (variable_data *)value;
    variable_data *to_insert =
        new variable_data(v_data->get_data_type(),
                          v_data->get_value());
    std::pair<std::string, item_data *>
        i_pair(id, to_insert);
    itm.insert(i_pair);
    return *this;
  }

  if (ITEM_TYPE_FCT == value->get_item_type())
  {
    function_data *f_data = (function_data *)value;
    function_data *to_insert = new function_data(*f_data);
    std::pair<std::string, item_data *>
        i_pair(id, to_insert);
    itm.insert(i_pair);
    return *this;
  }

  object_data *o_data = (object_data *)value;
  object_data *to_insert = new object_data(*o_data);
  std::pair<std::string, item_data *>
      i_pair(id, to_insert);
  itm.insert(i_pair);
  return *this;
}

/* used for type_table too
the only time when we don't check for previous scopes too
 */
item_data *symbol_table::get_data(const std::string &id) const
{
  if (itm.find(id) != itm.end())
    return (*itm.find(id)).second;
  return nullptr;
}

const std::string &symbol_table::get_id() const
{
  return s_id;
}

const size_t symbol_table::get_count() const
{
  return itm.size();
}

const size_t symbol_table::get_count_variable() const
{
  size_t count = 0;
  for (const auto &instance : itm)
    if (ITEM_TYPE_VAR ==
        instance.second->get_item_type())
      count++;
  return count;
}

const size_t symbol_table::get_count_function() const
{
  size_t count = 0;
  for (const auto &instance : itm)
    if (ITEM_TYPE_FCT ==
        instance.second->get_item_type())
      count++;
  return count;
}

const size_t symbol_table::get_count_object() const
{
  size_t count = 0;
  for (const auto &instance : itm)
    if (ITEM_TYPE_OBJ ==
        instance.second->get_item_type())
      count++;
  return count;
}

symbol_table::it symbol_table::begin()
{
  return itm.begin();
}

symbol_table::it symbol_table::end()
{
  return itm.end();
}

//!------------------------------------------------
//!------------------------------------------------

bool type_insert(const std::string &id,
                 const symbol_table &s)
{
  if (type_table.find(id) != type_table.end())
  {
    yyerror("class already defined");
    return false;
  }

  std::pair<std::string, symbol_table>
      s_pair(id, s);
  type_table.insert(s_pair);
  return true;
}

// DOES NOT provide error messages
symbol_table *type_exists(const std::string &id)
{
  if (type_table.find(id) != type_table.end())
    return &type_table.at(id);
  return nullptr;
}

#endif
