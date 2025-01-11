#ifndef ASTNODES_H
#define ASTNODES_H

#include <string>

/**
 * Forward-declare your SymbolTable class or replace with your actual class name.
 * This ensures we don't need the full definition of SymbolTable here.
 */
class SymbolTable;

/**
 * Base class for all AST nodes.
 *
 * Fields:
 * - `type`       : The semantic/data type of the node (e.g., "int", "float", "bool", "void", etc.).
 * - `lineNumber` : The line number in the source code for debugging or error messages.
 */
class ASTNode {
public:
    std::string type;  
    int lineNumber;

    virtual ~ASTNode() = default;

    /**
     * Evaluate or process this node. 
     * In an interpreter, you'd compute its value.
     * In a semantic analyzer, you'd do type checks, etc.
     * In a compiler, you might generate code.
     */
    virtual void evaluate(SymbolTable* currentScope) = 0;
};

#endif // ASTNODES_H