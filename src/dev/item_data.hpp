#ifndef __0ITEMDATA0__
#define __0ITEMDATA0__

#include <string>

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

#endif
