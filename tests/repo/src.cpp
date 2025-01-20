#include <iostream>
#include <vector>
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

int better_errors()
{
    bool is_error = false, error_flag = false;

    if (error_flag |= is_error = false; is_error)
        std::cout << "error: " << __LINE__ << '\n';

    if (error_flag |= is_error = true; is_error)
        std::cout << "error: " << __LINE__ << '\n';

    if (error_flag |= is_error = false; is_error)
        std::cout << "error: " << __LINE__ << '\n';

    if (false == error_flag)
        std::cout << "success\n";
    else
        std::cout << "model ready to be used\n";

    return 0;
}

int test_types()
{
    const char *str = "defined_type";
    
    {
        type_insert(str, symbol_table(str));
    }

    symbol_table *scope_symbol = type_exists(str);

    {
        variable_data v_data(DATA_TYPE_INT);
        scope_symbol->insert("var", &v_data);
    }

    scope_symbol = type_exists(str);
    std::cout << scope_symbol->get_data("var")->get_data_type() << ' '
              << ((variable_data *)(scope_symbol->get_data("var")))->get_value()
              << '\n';

    return 0;
}
