#ifndef __0ASTCTRL0__
#define __0ASTCTRL0__

#include <string>
#include <vector>
#include "ast_base.hpp"

class ast_block : public ast_node
{
    std::vector<ast_node*> exressions;

public:
    ast_block(const std::vector<ast_node*>&);
    
    const std::string &evaluate() override;
};

class ast_if : public ast_node
{
    ast_node* desired_expression;
    ast_block* true_expression;
    ast_block* false_expression;

public:
    ast_if(ast_node*, ast_block*, ast_block*);

    const std::string &evaluate() override;
};

class ast_for : public ast_node
{
    ast_node* init_expression;
    ast_node* desired_expression;
    ast_node* increment_expression;
    ast_block* block_expression;

public:
    ast_for(ast_node*, ast_node*, ast_node*, ast_block*);

    const std::string &evaluate() override;
};

class ast_while : public ast_node
{
    ast_node* desired_expression;
    ast_block* block_expression;

public:
    ast_while(ast_node*, ast_block*);

    const std::string &evaluate() override;
};

class ast_assignement
{
    ast_node* left_expression;
    ast_node* right_expression;

public:
    ast_assignement(ast_node*, ast_block*);

    const std::string &evaluate();
};

#endif