#include <iostream>
#include <vector>

class a
{
public:
  ~a() { std::cout << "a - deconstructor\n"; }
};

// why it is deconstructed?
int main()
{
  std::vector<a> dada;
  dada.emplace_back();
  std::cout << "debug\n";
  dada.emplace_back();
  std::cout << "debug\n";
  dada.emplace_back();
  std::cout << "debug\n";
}
