#include <iostream>
#include <vector>
#include <array>

const char *DATA_TYPE_INTG = "int";
const char *DATA_TYPE_FLOT = "float";
const char *DATA_TYPE_CHAR = "char";
const char *DATA_TYPE_STRG = "string";
const char *DATA_TYPE_BOOL = "bool";
const char *RESERVED_TYPES[] =
    {DATA_TYPE_INTG, DATA_TYPE_FLOT,
     DATA_TYPE_CHAR, DATA_TYPE_STRG,
     DATA_TYPE_BOOL};
constexpr char COUNT_RESERVED_TYPES = 5;

bool is_primitive(const std::string &type)
{
  for (unsigned char i = 0; i < COUNT_RESERVED_TYPES; i++)
    if (std::string(RESERVED_TYPES[i]) == type)
      return true;
  return false;
}

class item_data
{
public:
  virtual ~item_data() = default;
  virtual item_data *evaluate(const size_t) { return nullptr; }

  virtual const std::string &get_data_type() const = 0;
};

class primitive_data : public item_data
{
  std::string data_type;

public:
  virtual ~primitive_data() = default;
  virtual const std::string &get_data_type() const { return data_type; };
  int a;
};

class object_data : public item_data
{
  std::string data_type;

public:
  virtual ~object_data() = default;
  virtual const std::string &get_data_type() const { return data_type; };
};

constexpr size_t LEVEL0 = 0;
constexpr size_t LEVEL1 = 1;
constexpr size_t LEVELMAX = 5;
// 7 seconds for 100
// 268435452 kills compilation and INT_MAX won't compile

//! actual new thing
std::string base_type(const std::string &array_type)
{
  size_t index = array_type.find('[');
  std::string result;
  result.append(array_type.c_str(), index);
  return result;
}

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

template <class T, size_t deep_level>
class array_data;

//! base case
template <class T>
class array_data<T, 0> : public item_data
{
  T structure;
  std::string data_type;

public:
  array_data(std::string complete_data_type,
             const size_t,
             const std::vector<size_t> &)
      : data_type(complete_data_type)
  {
  }

  const std::string &get_data_type() const override { return data_type; }
};

//! inductive case
template <class T, size_t deep_level>
class array_data : public item_data
{
  std::string data_type;
  typedef array_data<T, deep_level - 1> instance;
  std::vector<item_data *> m_array;

public:
  virtual ~array_data() = default;
  array_data(
      std::string,
      const size_t,
      const std::vector<size_t> &);


  virtual item_data *evaluate(const size_t) override;

  const std::string &get_data_type() const override;
  const item_data *get_value(const size_t) const;
};

template <class T, size_t deep_level>
array_data<T, deep_level>::
    array_data(
        std::string complete_data_type,
        const size_t index_level,
        const std::vector<
            size_t> &level_data)
    : data_type(complete_data_type)
{

  size_t size = level_data.at(index_level);
  m_array.reserve(size);
  remove_level(complete_data_type);

  if (LEVEL1 == deep_level)
  {
    for (size_t i = 0; i < size; i++)
      m_array.emplace_back(new instance(
          complete_data_type, 0, level_data));
    return;
  }

  for (size_t i = 0; i < size; i++)
    m_array.emplace_back(new instance(
        complete_data_type,
        index_level + 1,
        level_data));
}

template <class T, size_t deep_level>
item_data *
array_data<T, deep_level>::
    evaluate(const size_t index)
{
  return m_array[index];
}

template <class T, size_t deep_level>
const std::string &
array_data<T, deep_level>::
    get_data_type() const
{
  return data_type;
}

template <class T, size_t deep_level>
const item_data *
array_data<T, deep_level>::
    get_value(const size_t index) const
{
  return m_array.at(index);
}

//! main
namespace dynamic_array
{
  template <class T, size_t index>
  item_data *array_for_index(
      const std::string &data_type,
      const std::vector<size_t> &level_data)
  {
    return new array_data<T, index>(
        data_type, 0,
        level_data);
  }

  template <class T, size_t... indexes>
  auto init_array(
      const std::string &data_type,
      const std::vector<size_t> &level_data,
      size_t i, std::index_sequence<indexes...>)
  {
    using function = item_data *(*)(const std::string &,
                                    const std::vector<size_t> &);
    constexpr function f[] = {array_for_index<T, indexes>...};
    return f[i](data_type, level_data);
  }
}

item_data *init_array(const std::string &data_type,
                      const std::vector<size_t> &level_data)
{
  if (level_data.size() >= LEVELMAX)
    std::cout << "this array has an impossible deep level.\n";

  if (is_primitive(base_type(data_type)))
    return dynamic_array::init_array<primitive_data>(
        data_type, level_data,
        level_data.size(),
        std::make_index_sequence<LEVELMAX>());

  return dynamic_array::init_array<object_data>(
      data_type, level_data,
      level_data.size(),
      std::make_index_sequence<LEVELMAX>());
}

// using std::array instead of std::vector makes compilation inneficient
// idea: https://stackoverflow.com/questions/68839163/
int main()
{
  std::string my_type = "int[2][3][4][5]";
  std::vector<size_t> level_data{2, 3, 4, 5};

  item_data *arr = init_array(my_type, level_data);
  std::cout << arr->get_data_type() << "\n";

  item_data *sub_arr = arr->evaluate(0);
  std::cout << sub_arr->get_data_type() << "\n";

  delete arr;
  return EXIT_SUCCESS;
}