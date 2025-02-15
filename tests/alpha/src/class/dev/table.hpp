#ifndef __0TABLE0__
#define __0TABLE0__

#include <string>

constexpr char SYMB_TYPE_INVALID = 4;

class symbol_data;

class table
{
public:
  virtual ~table() = default;
  virtual const size_t get_count(const char = SYMB_TYPE_INVALID) const = 0;
};

#endif
