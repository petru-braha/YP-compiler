#include <iostream>
#include <vector>
#include <numeric>

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
};

class primitive_data : public item_data
{
public:
  virtual ~primitive_data() = default;
};

class object_data : public item_data
{
public:
  virtual ~object_data() = default;
};

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

template <class T>
class array_data
{
public:
  size_t index, level;
  const std::vector<size_t> *level_data;
  std::string data_type;
  std::vector<T> m_array;

  virtual ~array_data() = default;
  array_data(std::string, const std::vector<size_t> &);

  void reset();
  void operator[](const size_t);
  T &get_value();
};

template <class T>
array_data<T>::array_data(
    std::string complete_data_type,
    const std::vector<size_t> &level_data)

    : index(0),
      level(0),
      level_data(&level_data),
      data_type(complete_data_type),
      m_array(std::accumulate(
          level_data.begin(), level_data.end(), 1,
          std::multiplies<size_t>()))
{
}

template <class T>
void array_data<T>::reset()
{
  index = level = 0;
}

template <class T>
void array_data<T>::operator[](const size_t idx)
{
  if (level >= level_data->size())
  {
    std::cout << "fail1\n";
    return;
  }
  if (idx >= level_data->at(level))
  {
    std::cout << "fail2\n";
    return;
  }

  size_t stride = std::accumulate(
      level_data->begin() + level + 1, level_data->end(), 1,
      std::multiplies<size_t>());
  stride *= idx;

  this->index += stride;
  level++;
}

template <class T>
T &array_data<T>::get_value()
{
  return m_array[index];
}

int main()
{
  std::string my_type = "int[2][3][4][5]";
  std::vector<size_t> level_data{2, 3, 4, 5};

  array_data<int> arr(my_type, level_data);
  arr[1];
  std::cout << arr.index << ' ' << arr.level << '\n';
  arr[2];
  std::cout << arr.index << ' ' << arr.level << '\n';
  arr[3];
  std::cout << arr.index << ' ' << arr.level << '\n';
  arr[4];
  std::cout << arr.index << ' ' << arr.level << '\n';
  arr[0];
  std::cout << arr.index << ' ' << arr.level << '\n';

  arr.get_value() = 1;

  return EXIT_SUCCESS;
}