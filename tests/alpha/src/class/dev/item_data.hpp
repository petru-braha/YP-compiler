#ifndef __0ITEMDATA0__
#define __0ITEMDATA0__

#include <string>
#include <yyerror.hpp>

constexpr char ITEM_TYPE_VAR = 0;
constexpr char ITEM_TYPE_FCT = 1;
constexpr char ITEM_TYPE_OBJ = 2;
constexpr char ITEM_TYPE_ARR = 3;

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

  virtual item_data *operator[](const size_t) = 0;
  
  virtual const char get_item_type() const = 0;
  virtual const std::string &get_data_type() const = 0;
};

#endif
