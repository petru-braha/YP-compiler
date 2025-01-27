#ifndef __0OBJARRAYDATA0__
#define __0OBJARRAYDATA0__

#include <vector>
#include <unordered_map>
#include "dev/item_data.hpp"
#include "object_data.hpp"

template<class T = object_data>
class obj_arry_data : public item_data
{
    std::vector<T> objects;

public:
    obj_arry_data(const std::string &);
    obj_arry_data(const std::string &, const obj_arry_data &);

    obj_arry_data &attribute_insert(const std::string &,
                                    item_data *const);
    obj_arry_data &set_attribute(const std::string &,
                                 item_data *const);

    const size_t get_count_attributes() const;
    item_data *get_attribute(const std::string &) const;
};

#endif
