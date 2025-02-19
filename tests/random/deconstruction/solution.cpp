#include <iostream>
#include <deque>
#include <vector>

class a
{
public:
  int value;
  ~a() { std::cout << "a - deconstructor\n"; }
  a(int value) : value(value) {}
  a() = delete;
  a(const a &&) = delete;
  a(const a &) { std::cout << "a - copy\n"; }
};
#include <vector>

int main()
{
  std::vector<a> dada;
  dada.reserve(2);
  dada.emplace_back(1);
  std::cout << "debug\n";
  dada.emplace_back(2);
  std::cout << "debug\n";
  dada.emplace_back(3);
  std::cout << "debug\n";
}
