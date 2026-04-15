#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codInterm.h"
#include "tabela_simbolos.h"
#include "globals.h"

#define LABEL_PREFIX "L"
#define LOCAL_SCOPE_SEP "::"

INSTRUCTION **intermediateCode = NULL;
int intermediateCodeCount = 0;

int intermediateCodeCapacity = 0;
int tempCounter = 0;
int labelCounter = 0;

char *duplicateString(const char *source) {
    size_t size;
    char *copy;

    if (source == NULL) {
        copy = (char *)calloc(1, sizeof(char));
        return copy;
    }

    size = strlen(source) + 1;
    copy = (char *)malloc(size);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, size);
    return copy;
}

ADDRESS makeEmptyAddress(void) {
    ADDRESS address;

    address.type = Empty;
    address.val = 0;
    address.booldReg = 0;
    address.name = NULL;

    return address;
}

ADDRESS makeConstAddress(int value) {
    ADDRESS address;

    address.type = IntConst;
    address.val = value;
    address.booldReg = 0;
    address.name = NULL;

    return address;
}

ADDRESS makeRegisterAddress(int reg) {
    ADDRESS address;

    address.type = IntConst;
    address.val = reg;
    address.booldReg = 1;
    address.name = NULL;

    return address;
}

ADDRESS makeStringAddress(const char *name, int booldReg) {
    ADDRESS address;

    address.type = String;
    address.val = 0;
    address.booldReg = booldReg;
    address.name = duplicateString(name);

    return address;
}

INSTRUCTION *createInstruction(const char *operatorName, ADDRESS arg1, ADDRESS arg2, ADDRESS arg3) {
    INSTRUCTION *instruction = (INSTRUCTION *)malloc(sizeof(INSTRUCTION));

    if (instruction == NULL) {
        return NULL;
    }

    instruction->operator = duplicateString(operatorName);
    instruction->arg1 = arg1;
    instruction->arg2 = arg2;
    instruction->arg3 = arg3;

    return instruction;
}

void ensureIntermediateCapacity(void) {
    INSTRUCTION **newBuffer;
    int newCapacity;

    if (intermediateCode == NULL) {
        intermediateCodeCapacity = MAX_INSTRUCTIONS;
        intermediateCode = (INSTRUCTION **)calloc((size_t)intermediateCodeCapacity, sizeof(INSTRUCTION *));
        return;
    }

    if (intermediateCodeCount < intermediateCodeCapacity) {
        return;
    }

    newCapacity = intermediateCodeCapacity * 2;
    if (newCapacity < 1) {
        newCapacity = MAX_INSTRUCTIONS;
    }

    newBuffer = (INSTRUCTION **)realloc(intermediateCode, (size_t)newCapacity * sizeof(INSTRUCTION *));
    if (newBuffer == NULL) {
        return;
    }

    memset(newBuffer + intermediateCodeCapacity, 0, (size_t)(newCapacity - intermediateCodeCapacity) * sizeof(INSTRUCTION *));

    intermediateCode = newBuffer;
    intermediateCodeCapacity = newCapacity;
}

void emitInstruction(const char *operatorName, ADDRESS arg1, ADDRESS arg2, ADDRESS arg3) {
    INSTRUCTION *instruction;

    ensureIntermediateCapacity();
    if (intermediateCode == NULL) {
        return;
    }

    if (intermediateCodeCount >= intermediateCodeCapacity) {
        return;
    }

    instruction = createInstruction(operatorName, arg1, arg2, arg3);
    if (instruction == NULL) {
        return;
    }

    intermediateCode[intermediateCodeCount++] = instruction;
}

void freeAddress(ADDRESS *address) {
    if (address == NULL) {
        return;
    }

    if (address->type == String && address->name != NULL) {
        free(address->name);
        address->name = NULL;
    }
}

void freeIntermediateCode(void) {
    int i;

    if (intermediateCode == NULL) {
        intermediateCodeCount = 0;
        intermediateCodeCapacity = 0;
        return;
    }

    for (i = 0; i < intermediateCodeCount; i++) {
        INSTRUCTION *instruction = intermediateCode[i];

        if (instruction == NULL) {
            continue;
        }

        free(instruction->operator);
        freeAddress(&instruction->arg1);
        freeAddress(&instruction->arg2);
        freeAddress(&instruction->arg3);
        free(instruction);
    }

    free(intermediateCode);
    intermediateCode = NULL;
    intermediateCodeCount = 0;
    intermediateCodeCapacity = 0;
}

const char *mapArithmeticOperator(const char *lexeme) {
    if (lexeme == NULL) {
        return NULL;
    }

    if (strcmp(lexeme, "+") == 0) {
        return "ADD";
    }
    if (strcmp(lexeme, "-") == 0) {
        return "SUB";
    }
    if (strcmp(lexeme, "*") == 0) {
        return "MULT";
    }
    if (strcmp(lexeme, "/") == 0) {
        return "DIV";
    }

    return NULL;
}

const char *mapRelationalOperator(const char *lexeme) {
    if (lexeme == NULL) {
        return NULL;
    }

    if (strcmp(lexeme, "==") == 0) {
        return "EQ";
    }
    if (strcmp(lexeme, "!=") == 0) {
        return "NEQ";
    }
    if (strcmp(lexeme, "<") == 0) {
        return "LT";
    }
    if (strcmp(lexeme, ">") == 0) {
        return "GT";
    }
    if (strcmp(lexeme, "<=") == 0) {
        return "LET";
    }
    if (strcmp(lexeme, ">=") == 0) {
        return "GET";
    }

    return NULL;
}

char *qualifyWithScope(const char *scope, const char *name) {
    size_t scopeSize;
    size_t nameSize;
    size_t sepSize;
    char *qualified;

    if (scope == NULL || name == NULL) {
        return duplicateString(name);
    }

    scopeSize = strlen(scope);
    nameSize = strlen(name);
    sepSize = strlen(LOCAL_SCOPE_SEP);

    qualified = (char *)malloc(scopeSize + sepSize + nameSize + 1);
    if (qualified == NULL) {
        return NULL;
    }

    memcpy(qualified, scope, scopeSize);
    memcpy(qualified + scopeSize, LOCAL_SCOPE_SEP, sepSize);
    memcpy(qualified + scopeSize + sepSize, name, nameSize + 1);

    return qualified;
}

char *resolveSymbolName(Item *symbolTable[], const char *name, const char *scope) {
    Item *item;

    if (name == NULL) {
        return duplicateString("");
    }

    if (symbolTable == NULL || scope == NULL) {
        return duplicateString(name);
    }

    item = searchtableAny(symbolTable, (char *)name, (char *)scope);
    if (item != NULL) {
        if (item->Statement != FunDeclK && strcmp(item->Scope, "global") != 0) {
            return qualifyWithScope(item->Scope, item->IDname);
        }
        return duplicateString(item->IDname);
    }

    return duplicateString(name);
}

const char *getDeclarationName(TreeNode *tree) {
    if (tree == NULL) {
        return NULL;
    }

    if (tree->stmtKind == VarDeclK && tree->child[0] != NULL) {
        return tree->child[0]->lexeme;
    }

    if (tree->stmtKind == VetDeclK) {
        if (tree->child[1] != NULL) {
            return tree->child[1]->lexeme;
        }
        if (tree->child[0] != NULL) {
            return tree->child[0]->lexeme;
        }
    }

    return NULL;
}

const char *getParameterName(TreeNode *tree) {
    if (tree == NULL) {
        return NULL;
    }

    if (tree->lexeme[0] != '\0') {
        return tree->lexeme;
    }

    if (tree->child[0] != NULL) {
        return tree->child[0]->lexeme;
    }

    return NULL;
}

int getArraySize(TreeNode *tree) {
    int size;

    if (tree == NULL || tree->stmtKind != VetDeclK) {
        return 1;
    }

    if (tree->child[0] == NULL) {
        return 1;
    }

    size = atoi(tree->child[0]->lexeme);
    if (size <= 0) {
        return 1;
    }

    return size;
}

int nextLabelId(void) {
    return labelCounter++;
}

ADDRESS makeLabelAddress(int id) {
    char buffer[32];

    snprintf(buffer, sizeof(buffer), "%s%d", LABEL_PREFIX, id);
    return makeStringAddress(buffer, 2);
}

int isVoidFunction(Item *symbolTable[], const char *functionName) {
    Item *functionItem;

    if (symbolTable == NULL || functionName == NULL) {
        return 0;
    }

    functionItem = searchtableExp(symbolTable, (char *)functionName, "global", AtivK);
    if (functionItem == NULL) {
        return 0;
    }

    return functionItem->DataType == Type_void;
}

ADDRESS ensureRegister(ADDRESS valueAddress) {
    ADDRESS destination;

    if (valueAddress.booldReg == 1) {
        return valueAddress;
    }

    destination = makeRegisterAddress(tempCounter++);

    if (valueAddress.type == String && valueAddress.name != NULL) {
        emitInstruction("LOAD", destination, valueAddress, makeEmptyAddress());
    } else if (valueAddress.type == IntConst) {
        emitInstruction("LOADI", destination, valueAddress, makeEmptyAddress());
    } else {
        emitInstruction("LOADI", destination, makeConstAddress(0), makeEmptyAddress());
    }

    return destination;
}

void generateDeclaration(TreeNode *tree, Item *symbolTable[], const char *scope) {
    ADDRESS symbolAddress;
    char *resolvedName;
    const char *declName;
    int allocationSize;

    if (tree == NULL) {
        return;
    }

    declName = getDeclarationName(tree);
    if (declName == NULL) {
        return;
    }

    resolvedName = resolveSymbolName(symbolTable, declName, scope);
    if (resolvedName == NULL) {
        return;
    }

    allocationSize = (tree->stmtKind == VetDeclK) ? getArraySize(tree) : 1;

    symbolAddress = makeStringAddress(resolvedName, 0);
    emitInstruction("ALLOC", symbolAddress, makeConstAddress(allocationSize), makeEmptyAddress());

    free(resolvedName);
}

ADDRESS generateExpression(TreeNode *tree, Item *symbolTable[], const char *scope) {
    ADDRESS destination;
    ADDRESS leftAddress;
    ADDRESS rightAddress;
    ADDRESS indexAddress;
    ADDRESS argumentAddress;
    ADDRESS symbolAddress;
    const char *mappedOperator;
    char *resolvedName;

    if (tree == NULL) {
        return makeEmptyAddress();
    }

    if (tree->nodeKind != ExpK) {
        generateNode(tree, symbolTable, scope, 0);
        return makeEmptyAddress();
    }

    switch (tree->expKind) {
        case ConstK:
            destination = makeRegisterAddress(tempCounter++);
            emitInstruction("LOADI", destination, makeConstAddress(atoi(tree->lexeme)), makeEmptyAddress());
            return destination;

        case IdK:
            resolvedName = resolveSymbolName(symbolTable, tree->lexeme, scope);
            if (resolvedName == NULL) {
                return makeEmptyAddress();
            }
            destination = makeRegisterAddress(tempCounter++);
            symbolAddress = makeStringAddress(resolvedName, 0);
            emitInstruction("LOAD", destination, symbolAddress, makeEmptyAddress());
            free(resolvedName);
            return destination;

        case VetK:
            resolvedName = resolveSymbolName(symbolTable, tree->lexeme, scope);
            if (resolvedName == NULL) {
                return makeEmptyAddress();
            }

            indexAddress = makeEmptyAddress();
            if (tree->child[0] != NULL) {
                indexAddress = ensureRegister(generateExpression(tree->child[0], symbolTable, scope));
            }

            destination = makeRegisterAddress(tempCounter++);
            symbolAddress = makeStringAddress(resolvedName, 0);
            emitInstruction("LOAD", destination, symbolAddress, indexAddress);
            free(resolvedName);
            return destination;

        case OpK:
            mappedOperator = mapArithmeticOperator(tree->lexeme);
            if (mappedOperator == NULL) {
                return makeEmptyAddress();
            }

            leftAddress = ensureRegister(generateExpression(tree->child[0], symbolTable, scope));
            rightAddress = ensureRegister(generateExpression(tree->child[1], symbolTable, scope));

            destination = makeRegisterAddress(tempCounter++);
            emitInstruction(mappedOperator, destination, leftAddress, rightAddress);
            return destination;

        case OpRel:
            mappedOperator = mapRelationalOperator(tree->lexeme);
            if (mappedOperator == NULL) {
                return makeEmptyAddress();
            }

            leftAddress = ensureRegister(generateExpression(tree->child[0], symbolTable, scope));
            rightAddress = ensureRegister(generateExpression(tree->child[1], symbolTable, scope));

            destination = makeRegisterAddress(tempCounter++);
            emitInstruction(mappedOperator, destination, leftAddress, rightAddress);
            return destination;

        case AssignK:
            rightAddress = ensureRegister(generateExpression(tree->child[1], symbolTable, scope));

            if (tree->child[0] == NULL) {
                return rightAddress;
            }

            if (tree->child[0]->expKind == IdK) {
                resolvedName = resolveSymbolName(symbolTable, tree->child[0]->lexeme, scope);
                if (resolvedName == NULL) {
                    return rightAddress;
                }

                emitInstruction("ASSIGN", makeStringAddress(resolvedName, 0), rightAddress, makeEmptyAddress());
                emitInstruction("STORE", rightAddress, makeStringAddress(resolvedName, 0), makeEmptyAddress());
                free(resolvedName);
                return rightAddress;
            }

            if (tree->child[0]->expKind == VetK) {
                resolvedName = resolveSymbolName(symbolTable, tree->child[0]->lexeme, scope);
                if (resolvedName == NULL) {
                    return rightAddress;
                }

                indexAddress = makeEmptyAddress();
                if (tree->child[0]->child[0] != NULL) {
                    indexAddress = ensureRegister(generateExpression(tree->child[0]->child[0], symbolTable, scope));
                }

                emitInstruction("ASSIGN", makeStringAddress(resolvedName, 0), rightAddress, indexAddress);
                emitInstruction("STORE", rightAddress, makeStringAddress(resolvedName, 0), indexAddress);
                free(resolvedName);
                return rightAddress;
            }

            return rightAddress;

        case AtivK:
        {
            int argumentCount = 0;
            TreeNode *argumentNode = tree->child[0];

            while (argumentNode != NULL) {
                argumentAddress = ensureRegister(generateExpression(argumentNode, symbolTable, scope));
                emitInstruction("PARAM", argumentAddress, makeEmptyAddress(), makeEmptyAddress());

                argumentCount++;
                argumentNode = argumentNode->sibling;
            }

            if (isVoidFunction(symbolTable, tree->lexeme)) {
                emitInstruction("CALL", makeStringAddress(tree->lexeme, 0), makeConstAddress(argumentCount), makeEmptyAddress());
                return makeEmptyAddress();
            }

            destination = makeRegisterAddress(tempCounter++);
            emitInstruction("CALL", makeStringAddress(tree->lexeme, 0), makeConstAddress(argumentCount), destination);
            return destination;
        }

        default:
            return makeEmptyAddress();
    }
}

void generateFunction(TreeNode *tree, Item *symbolTable[]) {
    TreeNode *parameter;
    TreeNode *body;
    const char *functionName;
    const char *parameterName;
    char *resolvedName;

    if (tree == NULL || tree->child[1] == NULL) {
        return;
    }

    functionName = tree->child[1]->lexeme;

    emitInstruction("FUN", makeStringAddress(functionName, 0), makeEmptyAddress(), makeEmptyAddress());

    parameter = tree->child[0];
    if (parameter != NULL && !(parameter->nodeKind == StmtK && parameter->stmtKind == ParamVoid)) {
        while (parameter != NULL) {
            parameterName = getParameterName(parameter);
            if (parameterName != NULL) {
                resolvedName = resolveSymbolName(symbolTable, parameterName, functionName);
                if (resolvedName != NULL) {
                    emitInstruction("ARG", makeStringAddress(resolvedName, 0), makeEmptyAddress(), makeEmptyAddress());
                    free(resolvedName);
                }
            }
            parameter = parameter->sibling;
        }
    }

    body = tree->child[2];
    generateNode(body, symbolTable, functionName, 1);

    if (strcmp(tree->lexeme, "VOID") == 0) {
        emitInstruction("RET", makeEmptyAddress(), makeEmptyAddress(), makeEmptyAddress());
    }

    emitInstruction("END", makeStringAddress(functionName, 0), makeEmptyAddress(), makeEmptyAddress());
}

void generateStatement(TreeNode *tree, Item *symbolTable[], const char *scope) {
    ADDRESS conditionAddress;
    ADDRESS returnAddress;
    int falseLabel;
    int endLabel;
    int startLabel;

    if (tree == NULL) {
        return;
    }

    switch (tree->stmtKind) {
        case VarDeclK:
        case VetDeclK:
            generateDeclaration(tree, symbolTable, scope);
            break;

        case FunDeclK:
            generateFunction(tree, symbolTable);
            break;

        case IfK:
            conditionAddress = ensureRegister(generateExpression(tree->child[0], symbolTable, scope));

            falseLabel = nextLabelId();
            if (tree->child[2] != NULL) {
                endLabel = nextLabelId();

                emitInstruction("IFF", conditionAddress, makeLabelAddress(falseLabel), makeEmptyAddress());
                generateNode(tree->child[1], symbolTable, scope, 1);
                emitInstruction("GOTO", makeLabelAddress(endLabel), makeEmptyAddress(), makeEmptyAddress());
                emitInstruction("LABEL", makeLabelAddress(falseLabel), makeEmptyAddress(), makeEmptyAddress());
                generateNode(tree->child[2], symbolTable, scope, 1);
                emitInstruction("LABEL", makeLabelAddress(endLabel), makeEmptyAddress(), makeEmptyAddress());
            } else {
                emitInstruction("IFF", conditionAddress, makeLabelAddress(falseLabel), makeEmptyAddress());
                generateNode(tree->child[1], symbolTable, scope, 1);
                emitInstruction("LABEL", makeLabelAddress(falseLabel), makeEmptyAddress(), makeEmptyAddress());
            }
            break;

        case WhileK:
            startLabel = nextLabelId();
            endLabel = nextLabelId();

            emitInstruction("LABEL", makeLabelAddress(startLabel), makeEmptyAddress(), makeEmptyAddress());
            conditionAddress = ensureRegister(generateExpression(tree->child[0], symbolTable, scope));
            emitInstruction("IFF", conditionAddress, makeLabelAddress(endLabel), makeEmptyAddress());
            generateNode(tree->child[1], symbolTable, scope, 1);
            emitInstruction("GOTO", makeLabelAddress(startLabel), makeEmptyAddress(), makeEmptyAddress());
            emitInstruction("LABEL", makeLabelAddress(endLabel), makeEmptyAddress(), makeEmptyAddress());
            break;

        case ReturnInK:
            returnAddress = ensureRegister(generateExpression(tree->child[0], symbolTable, scope));
            emitInstruction("RET", returnAddress, makeEmptyAddress(), makeEmptyAddress());
            break;

        case ReturnVoidK:
            emitInstruction("RET", makeEmptyAddress(), makeEmptyAddress(), makeEmptyAddress());
            break;

        default:
            break;
    }
}

void generateNode(TreeNode *tree, Item *symbolTable[], const char *scope, int traverseSiblings) {
    if (tree == NULL) {
        return;
    }

    if (tree->nodeKind == StmtK) {
        generateStatement(tree, symbolTable, scope);
    } else if (tree->nodeKind == ExpK) {
        (void)generateExpression(tree, symbolTable, scope);
    }

    if (traverseSiblings && tree->sibling != NULL) {
        generateNode(tree->sibling, symbolTable, scope, 1);
    }
}

void buildIntermediateCode(NODEPOINTER syntaxTree, Item *symbolTable[], int traverseSiblings) {
    freeIntermediateCode();

    tempCounter = 0;
    labelCounter = 0;

    if (syntaxTree == NULL) {
        return;
    }

    generateNode(syntaxTree, symbolTable, "global", traverseSiblings != 0);
}

void addressToString(const ADDRESS *address, char *buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return;
    }

    if (address == NULL || address->type == Empty) {
        snprintf(buffer, size, "_");
        return;
    }

    if (address->booldReg == 1) {
        snprintf(buffer, size, "r%d", address->val);
        return;
    }

    if (address->type == IntConst) {
        snprintf(buffer, size, "%d", address->val);
        return;
    }

    if (address->type == String && address->name != NULL) {
        snprintf(buffer, size, "%s", address->name);
        return;
    }

    snprintf(buffer, size, "_");
}

void addressToQuadString(const ADDRESS *address, char *buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return;
    }

    if (address == NULL || address->type == Empty) {
        snprintf(buffer, size, "-");
        return;
    }

    if (address->booldReg == 1) {
        snprintf(buffer, size, "$t%d", address->val);
        return;
    }

    if (address->type == IntConst) {
        snprintf(buffer, size, "%d", address->val);
        return;
    }

    if (address->type == String && address->name != NULL) {
        snprintf(buffer, size, "%s", address->name);
        return;
    }

    snprintf(buffer, size, "-");
}

void printIntermediateCode(FILE *out) {
    int i;

    if (out == NULL) {
        out = stdout;
    }

    fprintf(out, "\n============== CODIGO INTERMEDIARIO ==============\n");

    for (i = 0; i < intermediateCodeCount; i++) {
        INSTRUCTION *instruction = intermediateCode[i];
        char arg1[96];
        char arg2[96];
        char arg3[96];

        if (instruction == NULL) {
            continue;
        }

        addressToString(&instruction->arg1, arg1, sizeof(arg1));
        addressToString(&instruction->arg2, arg2, sizeof(arg2));
        addressToString(&instruction->arg3, arg3, sizeof(arg3));

        if (instruction->arg2.type == Empty && instruction->arg3.type == Empty) {
            fprintf(out, "%04d: %-8s %s\n", i, instruction->operator, arg1);
        } else if (instruction->arg3.type == Empty) {
            fprintf(out, "%04d: %-8s %s, %s\n", i, instruction->operator, arg1, arg2);
        } else {
            fprintf(out, "%04d: %-8s %s, %s, %s\n", i, instruction->operator, arg1, arg2, arg3);
        }
    }

    fprintf(out, "===================================================\n");
}

void printIntermediateQuadruples(FILE *out) {
    int i;

    if (out == NULL) {
        out = stdout;
    }

    fprintf(out, "\n============== QUADRUPLAS ==============\n");

    for (i = 0; i < intermediateCodeCount; i++) {
        INSTRUCTION *instruction = intermediateCode[i];
        char arg1[96];
        char arg2[96];
        char arg3[96];
        const char *opName;

        if (instruction == NULL) {
            continue;
        }

        opName = (instruction->operator != NULL) ? instruction->operator : "-";

        addressToQuadString(&instruction->arg1, arg1, sizeof(arg1));
        addressToQuadString(&instruction->arg2, arg2, sizeof(arg2));
        addressToQuadString(&instruction->arg3, arg3, sizeof(arg3));

        fprintf(out, "(%s, %s, %s, %s)\n", opName, arg1, arg2, arg3);
    }

    fprintf(out, "=========================================\n");
}
