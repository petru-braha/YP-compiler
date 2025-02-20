#include <iostream>
#include <vector>
#include <string.h>

int main()
{
  char data_type[] = "int[62][2646][5621237][697][97][367]";
  std::vector<size_t> level_data;
  level_data.reserve(10);
  char *number = strtok(data_type, "[]");
  number = strtok(NULL, "[]"); // skip the base type
  while (number)
  {
    level_data.emplace_back(atoll(number));
    number = strtok(NULL, "[]");
  }

  for (size_t i = 0; i < level_data.size(); i++)
    std::cout << level_data.at(i) << ' ';
  std::cout << '\n';
}