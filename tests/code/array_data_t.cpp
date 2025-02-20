#include "../../src/class/array_data.hpp"
#include "../../src/implementation.hpp"
#include "../../src/ast_call.hpp"

FILE *yyin;
char *yytext;
int yylineno;

/* test the following operators:
 * arr = arr
 * arr = subarr
 * subarr = arr
 * subarr = subarr
 * elem = arr
 * elem = subarr
 */

int main()
{
  std::vector<size_t> level_data = {2, 3, 4};
  array_data arr(level_data, new primitive_data("int", "5"));

  arr[1];
  arr[2];
  arr[3];
  primitive_data *variable = (primitive_data *)arr.get_value();
  variable->set_value("10");
  arr.reset();

  arr[1];
  arr[2];
  arr[2];
  printf("%s\n", ((primitive_data *)arr.get_value())->get_value().c_str());
  arr.reset();

  arr[1];
  arr[2];
  arr[3];
  printf("%s\n", ((primitive_data *)arr.get_value())->get_value().c_str());
  arr.reset();

  arr[1];
  array_data subarr(arr.get_data_type(), arr);
  printf("%s\n", subarr.get_data_type().c_str());
  arr.reset();

  subarr[2];
  subarr[2];
  printf("%s\n", ((primitive_data *)subarr.get_value())->get_value().c_str());
  subarr.reset();

  subarr[2];
  subarr[3];
  printf("%s\n", ((primitive_data *)subarr.get_value())->get_value().c_str());
  subarr.reset();
}
