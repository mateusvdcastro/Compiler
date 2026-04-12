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
    ADDRESS arg1;
    ADDRESS arg2;
    ADDRESS arg3;
} INSTRUCTION;

extern INSTRUCTION **intermediateCode;
extern int intermediateCodeCount;

void buildIntermediateCode(NODEPOINTER syntaxTree, Item *symbolTable[], int traverseSiblings);
void printIntermediateCode(FILE *out);
void freeIntermediateCode(void);

#endif
