#ifndef __0ITEMDATA0__
#define __0ITEMDATA0__

#include <string>

constexpr char PRMT_SYMB_TYPE = 0;
constexpr char FNCT_SYMB_TYPE = 1;
constexpr char OBJT_SYMB_TYPE = 2;
constexpr char ARRY_SYMB_TYPE = 3;
constexpr char SYMB_TYPE_INVALID = 4;

class mutable_data;

/* role: pointer cast of:
 * variable_data*
 * function_data*
 * object_data*
 * array_data*
 */
class symbol_data
{
public:
  virtual ~symbol_data() = default;
  virtual const char get_item_type() const = 0;
  virtual const std::string &get_data_type() const = 0;
};

class mutable_data : public symbol_data
{
public:
  virtual ~mutable_data() = default;
};

#endif
