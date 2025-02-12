#ifndef __0CONSTANT0__
#define __0CONSTANT0__

#include <string>

class item_data;

item_data* scope_search(const std::string &id);
bool is_type(const std::string &);
bool is_compatible(const char *type, const char *constant_value);

#endif
