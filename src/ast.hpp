#ifndef __0ASTNODES_H0__
#define __0ASTNODES_H0__

#include <string>
#include "symbol_table.hpp"

class ast_node
{
public:
    virtual ~ast_node() = default;
    virtual const std::string& evaluate(symbol_table*) = 0;
};

class ast_variable final : public ast_node
{
    const variable_data * const data;

public:
    ast_variable(const variable_data&);
    const std::string& evaluate(symbol_table*) override;
};

/* unary opearators are encoded here */
class ast_operation final : public ast_node
{
    std::string operation;
    ast_node* left_child;
    ast_node* rght_child;

public:
    ast_operation(ast_node*, ast_node*);
    const std::string& evaluate(symbol_table*) override;
};

#endif