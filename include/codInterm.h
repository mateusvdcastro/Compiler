#ifndef CodInterm_H
#define CodInterm_H 1

#include "tabela_simbolos.h"
#include "globals.h"

#define MAX_INSTRUCTIONS 1000
#define $zero 31
#define $ra 30
#define $fp 29
#define $sp 28
#define $temp 27
#define $s2 25
#define $s1 24
#define $s0 23
#define $temp2 22

typedef enum { Empty, IntConst, String } addressType;

typedef struct address {
    addressType type;
    int val; // For constants
    int booldReg; // Number (0), Reg (1), Label (2)
    char *name; // For labels
} ADDRESS;

typedef struct instruction {
    char *operator;
    ADDRESS arg1;
    ADDRESS arg2;
    ADDRESS arg3;
} INSTRUCTION;

extern INSTRUCTION** intermediateCode;


void buildIntermediateCode(NODEPOINTER syntaxTree, Item *symbolTable[], int boolean);

#endif