#ifndef __0VARARRAYDATA0__
#define __0VARARRAYDATA0__

#include <vector>
#include "dev/item_data.hpp"
#include "variable_data.hpp"

template<class T = variable_data>
class var_arry_data : public item_data
{
    std::vector<T> arr_values;

public:
    ~var_arry_data() = default;
    var_arry_data(const std::string &);
    var_arry_data(const std::string &, const std::string &);
    var_arry_data(const std::string &, const var_arry_data &);

    var_arry_data &set_value(const size_t, const std::string &);

    const std::string &get_value(const size_t) const;
};

#endif
