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
 * subarr = subarr x
 * elem = arr x
 * elem = subarr x
 */

std::vector<size_t> level_data = {2, 3, 4};
primitive_data *variable = nullptr;

void arr_arr(const array_data &arr)
{
  printf("arr_arr begin\n");
  array_data new_arr(level_data, new primitive_data("int", "60"));
  new_arr = arr;

  // 20
  new_arr[0];
  new_arr[0];
  new_arr[0];
  printf("%s\n", ((primitive_data *)new_arr.get_value())->get_value().c_str());
  new_arr.reset();

  // 30
  new_arr[0];
  new_arr[0];
  new_arr[1];
  printf("%s\n", ((primitive_data *)new_arr.get_value())->get_value().c_str());
  new_arr.reset();

  // 5
  new_arr[1];
  new_arr[2];
  new_arr[2];
  printf("%s\n", ((primitive_data *)new_arr.get_value())->get_value().c_str());
  new_arr.reset();

  printf("arr_arr end\n\n");
}

void arr_subarr(array_data &arr)
{
  printf("arr_subarr begin\n");
  std::vector<size_t> ld{4};
  array_data new_arr(ld, new primitive_data("int", "400"));
  arr[0];
  arr[1];
  new_arr = arr;
  arr.reset();

  // 5
  new_arr[0];
  printf("%s\n", ((primitive_data *)new_arr.get_value())->get_value().c_str());
  new_arr.reset();

  // 5
  new_arr[1];
  printf("%s\n", ((primitive_data *)new_arr.get_value())->get_value().c_str());
  new_arr.reset();

  // 5
  new_arr[2];
  printf("%s\n", ((primitive_data *)new_arr.get_value())->get_value().c_str());
  new_arr.reset();

  printf("arr_subarr end\n\n");
}

void subarr_arr(array_data &arr)
{
  printf("subarr_arr begin\n");
  std::vector<size_t> ld{2, 2, 2, 3, 4};
  array_data new_arr(ld, new primitive_data("int", "-1"));
  new_arr[0];
  new_arr[1];
  new_arr = arr;
  new_arr.reset();

  // -1
  new_arr[0];
  new_arr[0];
  new_arr[0];
  new_arr[0];
  new_arr[0];
  printf("%s\n", ((primitive_data *)new_arr.get_value())->get_value().c_str());
  new_arr.reset();

  // 30
  new_arr[0];
  new_arr[1];
  new_arr[0];
  new_arr[0];
  new_arr[1];
  printf("%s\n", ((primitive_data *)new_arr.get_value())->get_value().c_str());
  new_arr.reset();

  // 10
  new_arr[0];
  new_arr[1];
  new_arr[0];
  new_arr[0];
  new_arr[3];
  printf("%s\n", ((primitive_data *)new_arr.get_value())->get_value().c_str());
  new_arr.reset();

  printf("subarr_arr end\n\n");
}

void subarr_subarr(array_data &arr, array_data &subarr)
{
  printf("subarr_subarr begin\n");

  // assign 20 30 5 10
  subarr[2];
  subarr[0];

  // elem = arr
  variable = (primitive_data *)subarr.get_value();
  variable->set_value("20");
  subarr.reset();

  // elem = subarr
  subarr[2];
  subarr[1];
  variable = (primitive_data *)subarr.get_value();
  variable->set_value("30");
  subarr.reset();

  arr[0];
  arr[0];
  subarr[2];
  arr = subarr;
  arr.reset();
  subarr.reset();

  // 20
  arr[0];
  arr[0];
  arr[0];
  printf("%s\n", ((primitive_data *)arr.get_value())->get_value().c_str());
  arr.reset();

  // 30
  arr[0];
  arr[0];
  arr[1];
  printf("%s\n", ((primitive_data *)arr.get_value())->get_value().c_str());
  arr.reset();

  // 5
  arr[0];
  arr[0];
  arr[2];
  printf("%s\n", ((primitive_data *)arr.get_value())->get_value().c_str());
  arr.reset();

  // 10
  arr[0];
  arr[0];
  arr[3];
  printf("%s\n", ((primitive_data *)arr.get_value())->get_value().c_str());
  arr.reset();
  printf("subarr_subarr end\n\n");
}

int main()
{
  // construct
  array_data arr(level_data, new primitive_data("int", "5"));

  arr[1];
  arr[2];
  arr[3];
  variable = (primitive_data *)arr.get_value();
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

  // construct
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
  printf("%s\n\n", ((primitive_data *)subarr.get_value())->get_value().c_str());
  subarr.reset();

  subarr_subarr(arr, subarr);
  arr_arr(arr);
  arr_subarr(arr);
  subarr_arr(arr);
}
