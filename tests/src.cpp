#include <iostream>

int error_flags()
{
    bool error_flag = false, is_error = false;

    error_flag |= is_error = false;
    if (error_flag || is_error)
        std::cout << "error: " << __LINE__ << '\n';

    error_flag |= is_error = true;
    if (false == error_flag || false == is_error)
        std::cout << "error: " << __LINE__ << '\n';

    return 0;
}

#include "util.hpp"

std::vector<symbol_table> symbols;

int main()
{
    std::cout << sizeof(symbol_table) << ' ' << sizeof(type_table) << ' ';
    return 0;
}
