#include <iostream>
#include <vector>

constexpr size_t LEVEL0 = 0;
constexpr size_t LEVEL1 = 1;
constexpr size_t LEVEL2 = 2;
constexpr size_t LEVEL3 = 3;

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

class item_data
{
public:
  virtual const std::string &get_data_type() const = 0;
};

class variable_data : public item_data
{
public:
  int a;
};

template <const size_t>
class variable_array_data;

// base case
template <>
class variable_array_data<0> : public variable_data
{
  std::string data_type;

public:
  variable_array_data(std::string complete_data_type,
                      const size_t,
                      const size_t,
                      const std::vector<size_t> &)
      : data_type(complete_data_type)
  {
  }

  const std::string &get_data_type() const override { return data_type; }
};

// inductive case
template <const size_t deep_level>
class variable_array_data : public item_data
{
  std::string data_type;
  typedef variable_array_data<deep_level - 1> instance;
  std::vector<instance> m_array;

public:
  ~variable_array_data() = default;
  variable_array_data(std::string,
                      const size_t,
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
        const size_t size,
        const size_t index_level,
        const std::vector<
            size_t> &level_data)
    : data_type(complete_data_type)
{
  std::cout << deep_level;
  remove_level(complete_data_type);

  if (1 == deep_level)
  {
    for (size_t i = 0; i < size; i++)
      m_array.emplace_back(
          complete_data_type, 0, 0, level_data);
    return;
  }

  for (size_t i = 0; i < size; i++)
    m_array.emplace_back(
        complete_data_type,
        level_data.at(index_level + 1),
        index_level + 1,
        level_data);
}

template <const size_t deep_level>
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

item_data *init_array(const size_t deep_level);

int main()
{
  std::string my_type = "int[5][6][7]";
  std::vector<size_t> level_data;
  level_data.emplace_back(5);
  level_data.emplace_back(6);
  level_data.emplace_back(7);
  const size_t deep_level = level_data.size();

  if (deep_level == LEVEL3)
  {
    variable_array_data<LEVEL3>
        dada(my_type, level_data.at(0), 0, level_data);

    std::cout << "\n"
              << dada.get_data_type() << "\n";

    item_data *internal_array = dada[0];
    std::cout << internal_array->get_data_type() << "\n";
  }
}
