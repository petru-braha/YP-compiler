#ifndef __0INFO0__
#define __0INFO0__

#include <string>
#include "list.hpp"

class id_data
{
    std::string s_name, s_type, s_type_id;
    list parameters;

public:
    id_data(const char *, const char *,
            const char *);

    const char *get_name() const;
    const char *get_type() const;
    const char *get_type_id() const;
};

//------------------------------------------------
// constructors:

id_data::id_data(const char *name,
                 const char *type,
                 const char *type_id)
    : s_name(name), s_type(type), s_type_id(type_id) {}

//------------------------------------------------
// constant methods:

const char *id_data::get_name() const
{
    return s_name.c_str();
}

const char *id_data::get_type() const
{
    return s_type.c_str();
}

const char *id_data::get_type_id() const
{
    return s_type_id.c_str();
}

#endif
