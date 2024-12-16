#ifndef __0TYPEDATA0__
#define __0TYPEDATA0__

#include <string>

class type_data
{
    std::string *data;

public:
    ~type_data();
    type_data();
    type_data(std::string *type, int n);

    void add_fct_field();
    void add_var_field();
    void add_obj_field();
};

type_data::~type_data()
{
    delete[] data;
}

type_data::type_data(std::string *type, int n)
{
    data = new std::string[n];
    for (int i = 0; i < n; i++)
        data[i] = type[i];
}

#endif
