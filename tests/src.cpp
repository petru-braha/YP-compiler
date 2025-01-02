#include <iostream>
#include "util.hpp"
void yyerror(const char *s) {}
std::vector<symbol_table> symbols;

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

bool return_true()
{
    std::cout << "0";
    return true;
}

bool return_false()
{
    std::cout << "1";
    return false;
}

// 011
int old_main()
{
    if (return_true() && return_false())
        ;
    if (return_false() && return_true())
        ;
    return 0;
}

// doesn't yet work
int better_errors()
{
    bool is_error = false, error_flag = false;

    if (error_flag |= is_error = false && is_error)
        std::cout << "error: " << __LINE__ << '\n';

    if (error_flag |= is_error = true && is_error)
        std::cout << "error: " << __LINE__ << '\n';

    if (error_flag |= is_error = false && is_error)
        std::cout << "error: " << __LINE__ << '\n';

    return 0;
}

int main()
{
    better_errors();
}
