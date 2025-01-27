#ifndef __0FUNCTIONDATA0__
#define __0FUNCTIONDATA0__

#include <string>
#include <unordered_map>
#include "dev/item_data.hpp"

class object_data;
class symbol_table;

/* iterator methods required for function call */
class function_data final : public item_data
{
    std::unordered_map<
        std::string, item_data *>
        parameters;

    friend class object_data;
    friend class symbol_table;
    function_data(const function_data &);

    static std::string available_id;
    const std::string &default_id();

public:
    ~function_data();
    function_data();
    function_data(const std::string &);

    function_data &parameter_insert(item_data *const);
    function_data &parameter_insert(const std::string &,
                                    item_data *const);
    function_data &set_parameter(const std::string &,
                                 item_data *const);

    const size_t get_count_parameter() const;
    item_data *get_parameter(const std::string &) const;

    typedef std::unordered_map<
        std::string, item_data *>::iterator it;
    it begin();
    it end();
};

std::string function_data::available_id = "";

#endif
