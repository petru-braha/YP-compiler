#ifndef __0TABLE0__
#define __0TABLE0__

#include <string>

constexpr char ITEM_TYPE_INVALID = 4;

class item_data;

class table
{
public:
  virtual ~table() = default;
  virtual const size_t get_count(const char = ITEM_TYPE_INVALID) const = 0;
};

#endif
