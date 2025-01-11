#ifndef ASTSTATEMENTS_H
#define ASTSTATEMENTS_H

#include <vector>
#include "ASTNodes.hpp"  // Base class
#include "ASTExpressions.hpp" // If you need references to expressions

/**
 * A block of statements: { stmt1; stmt2; ... }
 */
class ASTBlockNode : public ASTNode {
public:
    std::vector<ASTNode*> statements; // Each element is typically a statement node

    ASTBlockNode(int line) {
        type = "void"; 
        lineNumber = line;
    }

    // Add a statement to the block.
    void addStatement(ASTNode* stmt) {
        statements.push_back(stmt);
    }

    void evaluate(SymbolTable* currentScope) override {
        for (auto* stmt : statements) {
            if (stmt) {
                stmt->evaluate(currentScope);
            }
        }
    }
};

/**
 * Assignment statement: leftValue = rightValue;
 */
class ASTAssignmentNode : public ASTNode {
public:
    ASTNode* left;   // Usually a variable or array access
    ASTNode* right;  // The expression to assign

    ASTAssignmentNode(ASTNode* lhs, ASTNode* rhs, int line)
        : left(lhs), right(rhs) {
        type = "void"; 
        lineNumber = line;
    }

    void evaluate(SymbolTable* currentScope) override {
        // Evaluate right side
        right->evaluate(currentScope);
        // Evaluate left side
        left->evaluate(currentScope);
        // If the language demands matching types, check left->type == right->type
        // If interpreting, update the symbol table with right's value
    }
};

/**
 * If statement: if (condition) thenBlock else elseBlock
 */
class ASTIfNode : public ASTNode {
public:
    ASTNode* condition;
    ASTNode* thenBlock; // typically an ASTBlockNode
    ASTNode* elseBlock; // optional, can be null

    ASTIfNode(ASTNode* cond, ASTNode* thenB, ASTNode* elseB, int line)
        : condition(cond), thenBlock(thenB), elseBlock(elseB) {
        type = "void";
        lineNumber = line;
    }

    void evaluate(SymbolTable* currentScope) override {
        condition->evaluate(currentScope);
        // if (condition->type != "bool") { /* error */ }
        // For interpretation, see if condition is true/false, evaluate the appropriate block
    }
};

/**
 * While statement: while (condition) { body }
 */
class ASTWhileNode : public ASTNode {
public:
    ASTNode* condition;
    ASTNode* body;

    ASTWhileNode(ASTNode* cond, ASTNode* bd, int line)
        : condition(cond), body(bd) {
        type = "void";
        lineNumber = line;
    }

    void evaluate(SymbolTable* currentScope) override {
        // while (true) {
        //   condition->evaluate(currentScope);
        //   if not true => break
        //   body->evaluate(currentScope);
        // }
    }
};

/**
 * For statement: for (init; condition; increment) { body }
 */
class ASTForNode : public ASTNode {
public:
    ASTNode* init;      
    ASTNode* condition; 
    ASTNode* increment; 
    ASTNode* body;      

    ASTForNode(ASTNode* i, ASTNode* c, ASTNode* inc, ASTNode* b, int line)
        : init(i), condition(c), increment(inc), body(b) {
        type = "void";
        lineNumber = line;
    }

    void evaluate(SymbolTable* currentScope) override {
        // init->evaluate(currentScope);
        // while(true) {
        //   condition->evaluate(currentScope);
        //   if not true => break
        //   body->evaluate(currentScope);
        //   increment->evaluate(currentScope);
        // }
    }
};

/**
 * Return statement: return someExpression;
 * If your language allows void returns, 'returnExpr' can be null.
 */
class ASTReturnNode : public ASTNode {
public:
    ASTNode* returnExpr;

    ASTReturnNode(ASTNode* expr, int line)
        : returnExpr(expr) {
        type = "void";
        lineNumber = line;
    }

    void evaluate(SymbolTable* currentScope) override {
        // Evaluate returnExpr if it exists
        // Then do something with the value (set a function-return state?).
    }
};

#endif // ASTSTATEMENTS_H