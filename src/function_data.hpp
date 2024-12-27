#ifndef __0FUNCTIONDATA0__
#define __0FUNCTIONDATA0__

#include <string>
#include <vector>
#include <dev/item_data.hpp>

class function_data final
{
    std::string return_type;
    std::vector<item_data *> parameters;

public:
    ~function_data();
    function_data(std::string &);
    function_data(std::string &,
                  const std::vector<item_data *> &);

    function_data &set_parameter(const size_t,
                                 item_data *const);

    const std::string &get_return_type() const;
    item_data *get_parameter(const size_t) const;
};

#endif
