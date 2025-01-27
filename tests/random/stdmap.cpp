#include <iostream>
#include <string>
#include <unordered_map>
#include "../alpha/src/data.hpp"

void yyerror(const char *s)
{
}

int main()
{
  std::unordered_map<std::string, item_data *> map;

  map["nr0"] = new variable_data("int", "0");
  map["nr1"] = new variable_data("int", "1");
  map["nr2"] = new variable_data("int", "2");

  map["pt0"] = new variable_data("float", "0.0");
  map["pt1"] = new variable_data("float", "1.0");
  map["pt2"] = new variable_data("float", "2.0");

  map["ch0"] = new variable_data("char", "\'0\'");
  map["ch1"] = new variable_data("char", "\'1\'");
  map["ch2"] = new variable_data("char", "\'2\'");

  map["tx0"] = new variable_data("string", "\"0\"");
  map["tx1"] = new variable_data("string", "\"1\"");
  map["tx2"] = new variable_data("string", "\"2\"");

  map["ft0"] = new variable_data("bool", "true");
  map["ft1"] = new variable_data("bool", "true");
  map["ft2"] = new variable_data("bool", "true");

  // new scope?
  map["nr3"] = new variable_data("int", "10");
  map["nr4"] = new variable_data("int", "11");
  map["nr5"] = new variable_data("int", "12");
  map["nr6"] = new variable_data("int", "13");

  map["curios"] = new variable_data("string", "\"why\"");

  for (const auto &i : map)
  {
    std::cout << i.first << " | " << i.second->get_data_type() << " | " << ((variable_data *)i.second)->get_value() << "\n";
    delete i.second;
  }

  /*string te_fut_in_gat;


    bool ft4 = ft1;
    bool ft5 = ft1;
    bool ft6 = true;
    */
}