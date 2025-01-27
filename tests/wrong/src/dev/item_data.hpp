#ifndef __0ITEMDATA0__
#define __0ITEMDATA0__

#include <string>
#include "yyerror.hpp"

constexpr unsigned char ITEM_TYPE_VAR = 0;
constexpr unsigned char ITEM_TYPE_FCT = 1;
constexpr unsigned char ITEM_TYPE_OBJ = 2;

/* role: provide pointers that can be used with
 * variable_data
 * function_data
 * object_data
 */
class item_data
{
    unsigned char item_type;
    std::string data_type;

public:
    virtual ~item_data() = default;
    item_data() = delete;
    item_data(const unsigned char,
              const std::string &);

    const unsigned char get_item_type() const;
    const std::string &get_data_type() const;
};

item_data::item_data(const unsigned char i_t,
                     const std::string &d_t)
    : item_type(i_t), data_type(d_t)
{
    if (i_t > ITEM_TYPE_OBJ)
        yyerror("wrong item type");
}

const unsigned char item_data::get_item_type() const
{
    return item_type;
}

const std::string &item_data::get_data_type() const
{
    return data_type;
}

#endif
