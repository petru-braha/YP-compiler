#include <iostream>

void test_bits()
{
  // 00000000 00000000 00000000 00000001 => adds bytes to the left
  char c = 1;
  void *ptr = &c;
  int value = *(int *)ptr;
  std::cout << value << '\n';

  // 00000001 00000000 00000000 00000001 => least significant bytes are kept
  value = 16777216 + 1;
  std::cout << (int)(char)value << '\n';
}

void test_print()
{
  char c = 1;
  void *ptr = &c;
  char *sme = (char *)ptr;
  char *ayl = &c;
  std::cout << ptr << ' ' << sme << ' ' << ayl << '\n';
}

struct complex_number
{
  double real, imag;
  complex_number(double one, double two)
      : real(one), imag(two) {}
};

void *f()
{
  return new complex_number(1616.620, 22647.075);
}

int main()
{
  complex_number *ptr = (complex_number *)f();
  std::cout << ptr->real << ' ' << ptr->imag << '\n';
  delete ptr;
  return EXIT_SUCCESS;
}
