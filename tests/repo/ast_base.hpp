#ifndef __0ASTNODE0__
#define __0ASTNODE0__

#include <string>
#include "util.hpp"

class ast_node
{
public:
    virtual ~ast_node() = default;
    virtual const std::string &get_data_type() const = 0;
    virtual const std::string &evaluate() = 0;
};

/* its type is predefined
 * leaf nodes
 * store a value
 */
class ast_variable final : public ast_node
{
    variable_data * const data;

public:
    ast_variable(variable_data *const);

    const std::string &get_data_type() const override;
    const std::string &evaluate() override;
};

ast_variable::ast_variable(variable_data *const v_data)
    : data(v_data)
{
}

const std::string &ast_variable::get_data_type() const
{
    return data->get_data_type();
}

const std::string &ast_variable::evaluate()
{
    return data->get_value();
}

/* its type is predefined
 * and determined by its children nodes
 * unary opearators are encoded here too (!, -)
 * store an operation
 */
class ast_operation final : public ast_node
{
    std::string operation;
    ast_node *left_child;
    ast_node *rght_child;

public:
    ast_operation(ast_node *, ast_node *);
    const std::string &evaluate() override;
};

#endif