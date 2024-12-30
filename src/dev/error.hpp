#ifndef __0ERROR0__
#define __0ERROR0__

#include "../../YP_utility.hpp"

extern std::vector<symbol_table> symbols;
#define LAST_SCOPE symbols.size() - 1

/* goes through every scope
 * could add extra traversal of the scopes
 * provides error messages
 * also checks if the id is treated as a type
 */
bool is_already_defined(const char *id)
{
    if (type_exists(id) || is_primitive(id))
    {
        yyerror("types used for identifier");
        return true;
    }

    for (size_t i = LAST_SCOPE;; i--)
    {
        if (symbols[LAST_SCOPE].exists(id))
        {
            yyerror("identifier already defined");
            return true;
        }

        if (0 == i)
            break;
    }

    return false;
}

/* a constant value can only be primitive
 * provides error messages
 */
bool is_type_compatible(const char *type, const char *constant_value)
{
    switch (constant_value[0])
    {
    default: // int
        if (nullptr == strchr(constant_value, '.'))
        {
            if (strcmp(type, DATA_TYPE_INT))
            {
                yyerror("incorrect parameter type");
                return false;
            }
            break;
        }

        // float
        if (strcmp(type, DATA_TYPE_FLT))
        {
            yyerror("incorrect parameter type");
            return false;
        }
        break;

    case '\'': // char
        if (strcmp(type, DATA_TYPE_CHR))
        {
            yyerror("incorrect parameter type");
            return false;
        }
        break;

    case 't': // bool
        if (strcmp(type, DATA_TYPE_BOL))
        {
            yyerror("incorrect parameter type");
            return false;
        }
        break;
    case 'f': // bool
        if (strcmp(type, DATA_TYPE_BOL))
        {
            yyerror("incorrect parameter type");
            return false;
        }
        break;

    case '\"': // string
        if (strcmp(type, DATA_TYPE_STR))
        {
            yyerror("incorrect parameter type");
            return false;
        }
        break;
    }

    return true;
}

#endif
