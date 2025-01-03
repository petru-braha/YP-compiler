#ifndef __0OBJECTDATA0__
#define __0OBJECTDATA0__

#include <vector>
#include "dev/item_data.hpp"

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

public:
    ~object_data();
    object_data();
    object_data(const std::string &);
    object_data(const std::string &, const object_data &);

    object_data &attribute_insert(const std::string &,
                                  item_data *const);
    object_data &set_attribute(const std::string &,
                               item_data *const);

    const size_t &get_count_attributes() const;
    item_data *get_attribute(const std::string &) const;

    typedef std::unordered_map<
        std::string, item_data *>::iterator it;
    it begin();
    it end();
};

#endif
