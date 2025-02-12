#include <iostream>

class a
{
public:
  int abaa() { return 1; }
};

class b : public a
{
  friend int dobe();
  int abaa() { return 2; }
};

int dobe()
{
  b dada;
  return dada.abaa();
}

int main()
{
  std::cout << dobe();
}
