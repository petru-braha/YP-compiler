#ifndef __0ITEMDATA0__
#define __0ITEMDATA0__

#include <string>

constexpr char PRMT_ITEM_TYPE = 0;
constexpr char FNCT_ITEM_TYPE = 1;
constexpr char OBJT_ITEM_TYPE = 2;
constexpr char ARRY_ITEM_TYPE = 3;

class mutable_data;

/* role: pointer cast of:
 * variable_data*
 * function_data*
 * object_data*
 * array_data*
 */
class item_data
{
public:
  virtual ~item_data() = default;
  virtual const char get_item_type() const = 0;
  virtual const std::string &get_data_type() const = 0;
};

class mutable_data : public item_data
{
public:
  virtual ~mutable_data() = default;
};

#endif
