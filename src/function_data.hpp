#ifndef __0FUNCTIONDATA0__
#define __0FUNCTIONDATA0__

#include <string>
#include <unordered_map>
#include <dev/item_data.hpp>

/* we prefer a map of parameters instead of a vector*/
class function_data final
{
    std::string return_type;
    std::unordered_map<
        std::string, item_data *>
        parameters;

    static std::string available_id;
    const std::string &default_id();

public:
    ~function_data();
    function_data(std::string &);

    function_data &parameter_insert(item_data *);
    function_data &parameter_insert(const std::string &,
                                    item_data *);
    function_data &set_parameter(const std::string &,
                                 item_data *);

    const std::string &get_return_type() const;
    size_t get_count_parameter() const;
    item_data *get_parameter(const std::string &) const;
};

std::string function_data::available_id = "";

#endif
