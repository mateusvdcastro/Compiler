#ifndef _COD_INTERM_H_
#define _COD_INTERM_H_ 1

#include <stdio.h>
#include "tabela_simbolos.h"
#include "globals.h"

#define MAX_INSTRUCTIONS 1000

/*
 * booldReg field in ADDRESS:
 * 0 = literal/symbol
 * 1 = virtual register
 * 2 = label
 */
typedef enum { Empty, IntConst, String } addressType;

typedef struct address {
    addressType type;
    int val;
    int booldReg;
    char *name;
} ADDRESS;

typedef struct instruction {
    char *operator;
    ADDRESS *arg1;
    ADDRESS *arg2;
    ADDRESS *arg3;
} INSTRUCTION;

void buildIntermediateCode(NODEPOINTER syntaxTree, Item *symbolTable[], int traverseSiblings);
void printIntermediateCode(FILE *out);
void printIntermediateQuadruples(FILE *out);
void freeIntermediateCode(void);

extern INSTRUCTION **intermediateCode;
extern int intermediateCodeCount;

extern int intermediateCodeCapacity;
extern int tempCounter;
extern int labelCounter;

ADDRESS makeEmptyAddress(void);
ADDRESS makeConstAddress(int value);
ADDRESS makeRegisterAddress(int reg);
ADDRESS makeStringAddress(const char *name, int booldReg);
INSTRUCTION *createInstruction(const char *operatorName, ADDRESS arg1, ADDRESS arg2, ADDRESS arg3);
void ensureIntermediateCapacity(void);
void emitInstruction(const char *operatorName, ADDRESS arg1, ADDRESS arg2, ADDRESS arg3);
void freeAddress(ADDRESS *address);
const char *mapArithmeticOperator(const char *lexeme);
const char *mapRelationalOperator(const char *lexeme);
ADDRESS ensureRegister(ADDRESS valueAddress);
ADDRESS generateExpression(TreeNode *tree, Item *symbolTable[], const char *scope);
void generateNode(TreeNode *tree, Item *symbolTable[], const char *scope, int traverseSiblings);
void generateStatement(TreeNode *tree, Item *symbolTable[], const char *scope);
void generateFunction(TreeNode *tree, Item *symbolTable[]);
void generateDeclaration(TreeNode *tree, Item *symbolTable[], const char *scope);
char *duplicateString(const char *source);
char *qualifyWithScope(const char *scope, const char *name);
char *resolveSymbolName(Item *symbolTable[], const char *name, const char *scope);
const char *getDeclarationName(TreeNode *tree);
const char *getParameterName(TreeNode *tree);
int getArraySize(TreeNode *tree);
int nextLabelId(void);
ADDRESS makeLabelAddress(int id);
int isVoidFunction(Item *symbolTable[], const char *functionName);
void addressToString(const ADDRESS *address, char *buffer, size_t size);
void addressToQuadString(const ADDRESS *address, char *buffer, size_t size);

#endif
