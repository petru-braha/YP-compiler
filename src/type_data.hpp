#ifndef __0TYPEDATA0__
#define __0TYPEDATA0__

#include <string>
#include "instance_data.hpp"

// stores fields
class type_data
{
    std::string *data;

public:
    ~type_data();
    type_data();
    
    const type_data& add_fct_field(const std::string&);
    const type_data& add_var_field(const std::string&);
    const type_data& add_obj_field(const std::string&);
};

//------------------------------------------------
// constructors:

type_data::~type_data()
{
    delete[] data;
}

type_data::type_data()
{
}

//------------------------------------------------
// specific functions:

const type_data& type_data::add_fct_field(const std::string& fct)
{
    
    return *this;
}

const type_data& type_data::add_var_field(const std::string& var)
{

    return *this;
}

const type_data& type_data::add_obj_field(const std::string& obj)
{

    return *this;
}

//------------------------------------------------
// constant functions:

#endif
