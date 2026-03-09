#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codInterm.h"
#include "tabela_simbolos.h"
#include "globals.h"

INSTRUCTION** intermediateCode = NULL;

INSTRUCTION* createInstruction(char *operator, ADDRESS arg1, ADDRESS arg2, ADDRESS arg3) {
    INSTRUCTION* instruction = (INSTRUCTION*)malloc(sizeof(INSTRUCTION));
    instruction->operator = strdup(operator); // strdup allocates memory and copies the string
    instruction->arg1 = arg1;
    instruction->arg2 = arg2;
    instruction->arg3 = arg3;
    return instruction;
}

ADDRESS* createAddress(addressType type, int val, int booldReg, char *name) {
    ADDRESS* address = (ADDRESS*)malloc(sizeof(ADDRESS));
    
    if (type == IntConst) {
        address->type = IntConst;
        address->val = val;
        address->booldReg = booldReg;
        address->name = NULL;
    } else if (type == String) {
        address->type = String;
        address->val = 0;
        address->name = strdup(name); // strdup allocates memory and copies the string
    } else {
        address->type = Empty;
        address->val = 0;
        address->name = NULL;
    }
    return address;
}


void createIntermediateCode(NODEPOINTER syntaxTree, Item *symbolTable[], int boolean) {
    // This function will traverse the syntax tree and generate intermediate code
    // The implementation will depend on the structure of the syntax tree and the symbol table
    if (syntaxTree == NULL) {
        return;
    }

    if (syntaxTree->nodeKind == StmtK) {
        switch (syntaxTree->stmtKind) {
            case IfK:
                // Generate code for if statement
                break;
            case WhileK:
                // Generate code for while statement
                break;
            case ReturnInK:
                // Generate code for return statement
                break;
            case ReturnVoidK:
                // Generate code for return void statement
                break;
            case VarDeclK:
                // Generate code for variable declaration
                break;
            case VetDeclK:
                // Generate code for array declaration
                break;
            case FunDeclK:
                // Generate code for function declaration
                break;
            default:
                break;
        }
    } else if (syntaxTree->nodeKind == ExpK) {
        switch (syntaxTree->expKind) {
            case OpK:
                // Generate code for operator
                break;
            case OpRel:
                // Generate code for relational operator
                break;
            case ConstK:
                // Generate code for constant numeric value
                break;
            case IdK:
                // Generate code for identifier
                break;
            case VetK:
                // Generate code for array access
                break;
            case AtivK:
                // Generate code for function call
                break;
            case AssignK:
                // Generate code for assignment
                break;
            case TypeK:
                // Generate code for type
                break;
            default:
                break;
        }
    }

    if (boolean) {
        createIntermediateCode(syntaxTree->sibling, symbolTable, boolean);
    }
}