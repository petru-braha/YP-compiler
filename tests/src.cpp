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

int main()
{
    return 0;
}
