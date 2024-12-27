#ifndef __0OBJECTDATA0__
#define __0OBJECTDATA0__

#include <vector>
#include "dev/item_data.hpp"

void set_default_value(const object_data &);

// the methods will be stored in the type table
class object_data final : public item_data
{
    std::vector<item_data *> attributes;

public:
    ~object_data() = default;
    object_data(std::string &);
    object_data(std::string &,
                const std::vector<item_data *> &);
    object_data(const object_data &);

    object_data &set_attribute(const size_t,
                               item_data *const);

    item_data *get_attribute(const size_t) const;
};

#endif
