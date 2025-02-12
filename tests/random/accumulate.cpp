#include <iostream>
#include <numeric>
#include <vector>

int main()
{
  std::vector<size_t> arr{1, 2, 3, 4};
  size_t dada = std::accumulate(
      arr.begin(), arr.end(), 1, std::multiplies<size_t>());
}