#ifndef __0ITEMDATA0__
#define __0ITEMDATA0__

#include <string>

constexpr unsigned char ITEM_TYPE_VAR = 0;
constexpr unsigned char ITEM_TYPE_FCT = 1;
constexpr unsigned char ITEM_TYPE_OBJ = 2;

class item_data
{
    unsigned char item_type;
    std::string type;

protected:
    void set_item_type(const unsigned int);

public:
    ~item_data() = default;
    item_data() = delete;
    item_data(const unsigned char,
              const std::string &);

    const unsigned char get_item_type() const;
    const std::string &get_type() const;
};

#endif
