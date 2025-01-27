#ifndef __0OBJECTDATA0__
#define __0OBJECTDATA0__

#include <vector>
#include <unordered_map>
#include "dev/item_data.hpp"
#include "variable_data.hpp"
#include "type_table.hpp"

class function_data;
class symbol_table;

/* the methods will be stored in the type table
 * every object_data instance will !!! NOT !!! first contain pointers to
    variable_data instances
    and then pointers to object_data instances
 * the pointer order should be directed by the class
 * iterator methods are required for initialization
 */
class object_data final : public item_data
{
    std::unordered_map<std::string, item_data *> attributes;

    friend class function_data;
    friend class symbol_table;
    object_data(const object_data &);

public:
    ~object_data();
    object_data();
    object_data(const std::string &);
    object_data(const std::string &, const object_data &);

    object_data &attribute_insert(const std::string &,
                                  item_data *const);
    object_data &set_attribute(const std::string &,
                               item_data *const);

    const size_t get_count_attributes() const;
    item_data *get_attribute(const std::string &) const;

    typedef std::unordered_map<
        std::string, item_data *>::iterator it;
    it begin();
    it end();
};

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

    // TODO: to remove?
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

#endif
