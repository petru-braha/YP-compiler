#include <iostream>

class a{};

// using std::array instead of std::vector makes compilation inneficient
// idea: https://stackoverflow.com/questions/68839163/
int main()
{
  int array[5][5][5][5];
  array[0][0][0][0] = 1;
  std::cout << array[0][0][0][0] << "\n";

  return EXIT_SUCCESS;
}