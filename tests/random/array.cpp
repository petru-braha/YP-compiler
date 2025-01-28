#include <iostream>
#include <vector>

class item_data
{
};

class variable_data : public item_data
{
public:
  int a;
};

std::vector<size_t> level_data;

template <const size_t>
class variable_array_data;

template <>
class variable_array_data<0> : public variable_data
{
};

template <const size_t deep_level>
class variable_array_data : public item_data
{
  typedef variable_array_data<deep_level - 1> instance;
  std::vector<instance> m_array;

  variable_array_data(const size_t);

public:
  ~variable_array_data() = default;
  variable_array_data(const size_t,
                      const std::vector<size_t> *const);
  // construct also with values

  instance &get_value(const size_t) const;
};

template <size_t deep_level>
variable_array_data<deep_level>::
    variable_array_data(const size_t index_level,
                        const std::vector<
                            size_t> *const level_data)
{
  for (size_t index_size = 0;
       index_size < level_data->size(); index_size++)
    m_array.emplace_back(level_data->at(index_size), level_data);
}

int main()
{
  // int[5][5][5] dada;
  level_data.emplace_back(5);
  level_data.emplace_back(5);
  level_data.emplace_back(5);

  const size_t deep_level0 = level_data.size();

  variable_array_data<deep_level0> dada;
}
