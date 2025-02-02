#include <iostream>
#include <vector>
#include <array>

constexpr size_t LEVEL0 = 0;
constexpr size_t LEVEL1 = 1;
constexpr size_t LEVELMAX = 5;
// 7 seconds for 100
// 268435452 kills compilation and INT_MAX won't compile

void remove_level(std::string &data_type)
{
  size_t index0 = data_type.find('[');
  if (std::string::npos == index0)
    return;

  size_t index1 = data_type.find(']', index0);
  if (std::string::npos == index1)
  {
    std::cout << "bad";
    return;
  }

  std::string::const_iterator it0, it1;
  it0 = data_type.begin() + index0;
  it1 = it0 + (index1 - index0 + 1);
  data_type.erase(it0, it1);
}

//! help classes
class item_data
{
public:
  virtual ~item_data() = default;

  virtual const std::string &get_data_type() const = 0;
};

class variable_data : public item_data
{
public:
  virtual ~variable_data() = default;
  int a;
};

template <size_t>
class variable_array_data;

//! base case
template <>
class variable_array_data<0> : public variable_data
{
  std::string data_type;

public:
  variable_array_data(std::string complete_data_type,
                      const size_t,
                      const std::vector<size_t> &)
      : data_type(complete_data_type)
  {
  }

  const std::string &get_data_type() const override { return data_type; }
};

//! inductive case
template <const size_t deep_level>
class variable_array_data : public item_data
{
  std::string data_type;
  typedef variable_array_data<deep_level - 1> instance;
  std::vector<instance> m_array;

public:
  virtual ~variable_array_data() = default;
  variable_array_data(std::string,
                      const size_t,
                      const std::vector<size_t> &);
  // construct also with value
  item_data *operator[](const size_t);

  const std::string &get_data_type() const override;
  const item_data *get_value(const size_t) const;
};

template <size_t deep_level>
variable_array_data<deep_level>::
    variable_array_data(
        std::string complete_data_type,
        const size_t index_level,
        const std::vector<
            size_t> &level_data)
    : data_type(complete_data_type)
{

  std::cout << deep_level;
  size_t size = level_data.at(index_level);
  m_array.reserve(size);
  remove_level(complete_data_type);

  if (LEVEL1 == deep_level)
  {
    for (size_t i = 0; i < size; i++)
      m_array.emplace_back(
          complete_data_type, 0, level_data);
    return;
  }

  for (size_t i = 0; i < size; i++)
    m_array.emplace_back(
        complete_data_type,
        index_level + 1,
        level_data);
}

template <size_t deep_level>
item_data *
variable_array_data<deep_level>::operator[](const size_t index)
{
  return &m_array[index];
}

template <const size_t deep_level>
const std::string &
variable_array_data<deep_level>::
    get_data_type() const
{
  return data_type;
}

template <const size_t deep_level>
const item_data *
variable_array_data<deep_level>::
    get_value(const size_t index) const
{
  return &m_array.at(index);
}

//! main
namespace dynamic_array
{
  template <size_t index>
  item_data *array_for_index(
      const std::string &data_type,
      const std::vector<size_t> &level_data)
  {
    return new variable_array_data<index>(
        data_type, 0,
        level_data);
  }

  template <size_t... indexes>
  auto init_array(
      const std::string &data_type,
      const std::vector<size_t> &level_data,
      size_t i, std::index_sequence<indexes...>)
  {
    using function = item_data *(*)(const std::string &,
                                    const std::vector<size_t> &);
    constexpr function f[] = {array_for_index<indexes>...};
    return f[i](data_type, level_data);
  }
}

item_data *init_array(const std::string &data_type,
                      const std::vector<size_t> &level_data)
{
  if (level_data.size() >= LEVELMAX)
    std::cout << "bad\n";

  return dynamic_array::init_array(
      data_type, level_data,
      level_data.size(),
      std::make_index_sequence<LEVELMAX>());
}

// todo return the correct pointer type
// todo make this class available for any type
// todo reduce compilation time

// using std::array instead of std::vector makes compilation inneficient
// idea: https://stackoverflow.com/questions/68839163/
int main()
{
  std::string my_type = "int[2][3][4][5]";
  std::vector<size_t> level_data;
  level_data.emplace_back(2);
  level_data.emplace_back(3);
  level_data.emplace_back(4);
  level_data.emplace_back(5);

  item_data *arr = init_array(my_type, level_data);

  std::cout << "\n"
            << arr->get_data_type() << "\n";

  // item_data *internal_array = arr[0];
  // std::cout << internal_array->get_data_type() << "\n";

  delete arr;
  return EXIT_SUCCESS;
}
