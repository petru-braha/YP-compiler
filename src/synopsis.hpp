#ifndef __0SYNOPSIS0__
#define __0SYNOPSIS0__

#include <string>

/* these classes should not include name data_type:
redundancy - they are stored in instance_data;
* they include name */
class synopsis
{
};

template <class T>
class synopsis_variable final : public synopsis
{
    T value;

public:
    synopsis_variable(const char *);
    std::to_string(T);
};

class synopsis_function final : public synopsis
{
    // get function definition
    synopsis_variable<int> *values;
    synopsis_variable<float> *values;

public:
    synopsis_function(const char *, const char *);
};

class synopsis_class final : public synopsis
{
    // get class definition
    // VS string
    synopsis_variable<int> *values;
    synopsis_variable<float> *values;

public:
    ~synopsis_class();
    synopsis_class(const char *);
};

#endif
