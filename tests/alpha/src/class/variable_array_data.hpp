#ifndef __0VARARRAYDATA0__
#define __0VARARRAYDATA0__

#include <vector>
#include "dev/item_data.hpp"
#include "variable_data.hpp"

template <size_t nr>
class variable_array_data : public item_data
{
  std::vector<nr - 1> m_array;

public:
  ~var_arry_data() = default;
  var_arry_data(const size_t nr_para, ...);
  var_arry_data(const std::string &);
  var_arry_data(const std::string &, const std::string &);
  var_arry_data(const std::string &, const var_arry_data &);

  var_arry_data &set_value(const size_t, const std::string &);

  const std::string &get_value(const size_t) const;
};

template <>
class variable_array_data<0> : public variable_data
{
};

#endif
