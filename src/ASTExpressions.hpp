#ifndef ASTEXPRESSIONS_H
#define ASTEXPRESSIONS_H

#include <vector>
#include <string>
#include "ASTNodes.hpp"  // We need the base ASTNode

/**
 * Simple AST node for an integer literal (e.g., `42`).
 */
class ASTIntNode : public ASTNode {
public:
    int value;

    ASTIntNode(int val, int line) : value(val) {
        type = "int";
        lineNumber = line;
    }

    void evaluate(SymbolTable* currentScope) override {
        // For a literal, typically no further logic needed,
        // unless you store computed values somewhere.
    }
};

/**
 * AST node for float literals (e.g., `3.14`).
 */
class ASTFloatNode : public ASTNode {
public:
    float value;

    ASTFloatNode(float val, int line) : value(val) {
        type = "float";
        lineNumber = line;
    }

    void evaluate(SymbolTable* currentScope) override {
        // Same placeholder logic as int.
    }
};

/**
 * AST node for boolean literals: `true` or `false`.
 */
class ASTBoolNode : public ASTNode {
public:
    bool value;

    ASTBoolNode(bool val, int line) : value(val) {
        type = "bool";
        lineNumber = line;
    }

    void evaluate(SymbolTable* currentScope) override {
        // Same placeholder logic as int.
    }
};

/**
 * AST node for char literals (e.g. `'c'`).
 */
class ASTCharNode : public ASTNode {
public:
    char value;

    ASTCharNode(char val, int line) : value(val) {
        type = "char";
        lineNumber = line;
    }

    void evaluate(SymbolTable* currentScope) override {
        // Same placeholder logic as int.
    }
};

/**
 * AST node for string literals (e.g. `"Hello!"`).
 */
class ASTStringNode : public ASTNode {
public:
    std::string value;

    ASTStringNode(const std::string &val, int line) : value(val) {
        type = "string";
        lineNumber = line;
    }

    void evaluate(SymbolTable* currentScope) override {
        // Same placeholder logic as int.
    }
};

/**
 * AST node for referencing a variable (an identifier).
 */
class ASTVariableNode : public ASTNode {
public:
    std::string varName;

    ASTVariableNode(const std::string &name, int line) : varName(name) {
        type = "unknown"; // Will be determined after a lookup, if needed
        lineNumber = line;
    }

    void evaluate(SymbolTable* currentScope) override {
        // Example pseudo-logic:
        //  SymbolInfo* sym = currentScope->lookup(varName);
        //  if (!sym) { /* error: undefined */ }
        //  else { type = sym->dataType; }
    }
};

/**
 * Unary operation node (e.g., `!expr`, unary `-expr`).
 */
class ASTUnaryNode : public ASTNode {
public:
    std::string op;   // "!", "-" etc.
    ASTNode* operand; // single child

    ASTUnaryNode(const std::string &opr, ASTNode* opd, int line)
        : op(opr), operand(opd) {
        type = "unknown";
        lineNumber = line;
    }

    void evaluate(SymbolTable* currentScope) override {
        operand->evaluate(currentScope);
        // e.g., if op=="!" and operand->type!="bool", type error.
        // else type="bool".
    }
};

/**
 * Binary operation node (e.g., `expr1 + expr2`, `expr1 == expr2`, `expr1 && expr2`).
 */
class ASTBinaryNode : public ASTNode {
public:
    std::string op;   // "+", "-", "*", "/", "==", "&&", "||", etc.
    ASTNode* left;
    ASTNode* right;

    ASTBinaryNode(const std::string &opr, ASTNode* l, ASTNode* r, int line)
        : op(opr), left(l), right(r) {
        type = "unknown";
        lineNumber = line;
    }

    void evaluate(SymbolTable* currentScope) override {
        left->evaluate(currentScope);
        right->evaluate(currentScope);
        // If types differ, handle error or type promotion.
        // e.g., if both are "int" and op=="+", type="int".
    }
};

/**
 * Function call node (e.g., `Print(x)`, `Type(x+1)`, or user-defined).
 */
class ASTFunctionCallNode : public ASTNode {
public:
    std::string functionName;
    std::vector<ASTNode*> arguments;

    ASTFunctionCallNode(const std::string &fName, 
                        const std::vector<ASTNode*> &args,
                        int line)
        : functionName(fName), arguments(args) {
        type = "unknown";
        lineNumber = line;
    }

    void evaluate(SymbolTable* currentScope) override {
        // 1. Look up functionName in symbol table.
        // 2. Evaluate each argument.
        // 3. Check param count and types.
        // 4. Set type=the function's return type, if known.
    }
};

#endif // ASTEXPRESSIONS_H