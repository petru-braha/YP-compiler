#ifndef __0SYNOPSIS0__
#define __0SYNOPSIS0__

#include <string>

/* these classes should not include name data_type:
redundancy - they are stored in instance_data;
* they include name */
class synopsis
{
};

class synopsis_variable final : public synopsis
{
    std::string value;

public:
    synopsis_variable(const char *);
};

class synopsis_function final : public synopsis
{
    // get function definition
    // std::vector<synopsis_variable> parameters;

public:
    synopsis_function(const char *, const char *);
};

class synopsis_class final : public synopsis
{
    // get class definition
    // synopsis_variable<int> *values;

public:
    ~synopsis_class();
    synopsis_class(const char *);
};

#endif
