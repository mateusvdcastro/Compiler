#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codInterm.h"
#include "assembly.h"

ASSEMBLY **assemblyInstructions = NULL;
int assemblyCount = 0;

const char * op_names[] = {
    "ADD", "SUB", "MUL", "DIV",
    "AND", "OR", "NOT",
    "EQ", "NEQ", "LT", "GT", "GET", "LET",
    "LOAD", "LOADI","STORE", "ASSIGN", "ALLOC", "ARG",
    "GOTO", "IFF", "PARAM", "CALL", "RET", "LABEL", "FUN",
};

void generateAssembly(INSTRUCTION *instruction);
// Gerar código de montagem com base na instrução intermediária
// Esta função deve ser implementada para traduzir cada tipo de instrução intermediária
// para a representação de código de montagem correspondente.


void assembly (){
    initializeAssembly();

    /*Criar um Jump para a main */
    ASSEMBLY *jumpInstruction = createAssemblyNode(typeJ, "j");
    jumpInstruction->type_j->labelImediato = "main";
    assemblyInstructions[assemblyCount++] = jumpInstruction;

    for (int i = 0; i < intermediateCodeCount; i++){
        generateAssembly(intermediateCode[i]);
    }
}

void initializeAssembly(){
    assemblyInstructions = (ASSEMBLY **)malloc(MAX_ASSEMBLY * sizeof(ASSEMBLY *));
    assemblyCount = 0;

    for (int i = 0; i < MAX_ASSEMBLY; i++) {
        assemblyInstructions[i] = NULL;
    }

    // initializeLabels
    // initialize memory management for assembly instructions
    // currentFunctionn = memoryVector.functions
}

ASSEMBLY * createAssemblyNode(instruction_type_t type, char *nome){
    ASSEMBLY * newNode = (ASSEMBLY *)malloc(sizeof(ASSEMBLY));
    newNode->type = type;

    switch (type) {
        case typeR:
            newNode->type_r = (r_type_t *)malloc(sizeof(r_type_t));
            newNode->type_r->nome = strdup(nome);
            newNode->type_r->rd = -1;
            newNode->type_r->rs = -1;
            newNode->type_r->rt = -1;
            newNode->type_r->shamt = 0;
            break;
        case typeI:
            newNode->type_i = (i_type_t *)malloc(sizeof(i_type_t));
            newNode->type_i->nome = strdup(nome);
            newNode->type_i->rs = -1;
            newNode->type_i->rt = -1;
            newNode->type_i->imediato = -1;
            newNode->type_i->label = -1;
            break;
        case typeJ:
            newNode->type_j = (j_type_t *)malloc(sizeof(j_type_t));
            newNode->type_j->nome = strdup(nome);
            newNode->type_j->labelImediato = NULL;
            break;
        case typeLabel:
            newNode->type_label = (label_type_t *)malloc(sizeof(label_type_t));
            newNode->type_label->nome = strdup(nome);
            newNode->type_label->is_dynamic = -1;
            newNode->type_label->endereco = -1;
            break;
    }

    return newNode;
}

int aritmeticOp(INSTRUCTION * instruction, ASSEMBLY ** newInstruction){
    if (strcmp(instruction->operator, "ADD") == 0) {
        *newInstruction = createAssemblyNode(typeR, "add");
        (*newInstruction)->type_r->rd = instruction->arg1.val; // Registrador destino
        (*newInstruction)->type_r->rs = instruction->arg2.val; // Registrador fonte 1
        (*newInstruction)->type_r->rt = instruction->arg3.val; // Registrador fonte 2
    } else if (strcmp(instruction->operator, "SUB") == 0) {
        *newInstruction = createAssemblyNode(typeR, "sub");
        (*newInstruction)->type_r->rd = instruction->arg1.val; // Registrador destino
        (*newInstruction)->type_r->rs = instruction->arg2.val; // Registrador fonte 1
        (*newInstruction)->type_r->rt = instruction->arg3.val; // Registrador fonte 2
    } else if (strcmp(instruction->operator, "MULT") == 0) {
        *newInstruction = createAssemblyNode(typeR, "mul");
        (*newInstruction)->type_r->rd = instruction->arg1.val; // Registrador destino
        (*newInstruction)->type_r->rs = instruction->arg2.val; // Registrador fonte 1
        (*newInstruction)->type_r->rt = instruction->arg3.val; // Registrador fonte 2
    } else if (strcmp(instruction->operator, "DIV") == 0) {
        *newInstruction = createAssemblyNode(typeR, "div");
        (*newInstruction)->type_r->rd = instruction->arg1.val; // Registrador destino
        (*newInstruction)->type_r->rs = instruction->arg2.val; // Registrador fonte 1
        (*newInstruction)->type_r->rt = instruction->arg3.val; // Registrador fonte 2
    } else if (strcmp(instruction->operator, "AND") == 0) {
        *newInstruction = createAssemblyNode(typeR, "and");
        (*newInstruction)->type_r->rd = instruction->arg1.val; // Registrador destino
        (*newInstruction)->type_r->rs = instruction->arg2.val; // Registrador fonte 1
        (*newInstruction)->type_r->rt = instruction->arg3.val; // Registrador fonte 2
    } else if (strcmp(instruction->operator, "OR") == 0) {
        *newInstruction = createAssemblyNode(typeR, "or");
        (*newInstruction)->type_r->rd = instruction->arg1.val; // Registrador destino
        (*newInstruction)->type_r->rs = instruction->arg2.val; // Registrador fonte 1
        (*newInstruction)->type_r->rt = instruction->arg3.val; // Registrador fonte 2
    } else {
        return 0;
    }
    return 1;
}


int relationalOp(INSTRUCTION * instruction, ASSEMBLY ** newInstruction){
    int rd;
    
    if (strcmp(instruction->operator, "EQ") == 0) {
        *newInstruction = createAssemblyNode(typeR, "xor");
        (*newInstruction)->type_r->rd = instruction->arg1.val; 
        (*newInstruction)->type_r->rs = instruction->arg2.val; 
        (*newInstruction)->type_r->rt = instruction->arg3.val; 

        assemblyInstructions[assemblyCount++] = *newInstruction;

        (*newInstruction) = createAssemblyNode(typeI, "slti");
        (*newInstruction)->type_i->rt = instruction->arg1.val; 
        (*newInstruction)->type_i->rs = instruction->arg1.val; 
        (*newInstruction)->type_i->imediato = 1; // Valor imediato
    } else if (strcmp(instruction->operator, "NEQ") == 0) {
        *newInstruction = createAssemblyNode(typeR, "slt");
        (*newInstruction)->type_r->rd = $temp; 
        (*newInstruction)->type_r->rs = instruction->arg2.val; 
        (*newInstruction)->type_r->rt = instruction->arg3.val; 

        assemblyInstructions[assemblyCount++] = *newInstruction;

        (*newInstruction) = createAssemblyNode(typeR, "slt");
        (*newInstruction)->type_r->rd = instruction->arg1.val; 
        (*newInstruction)->type_r->rs = instruction->arg3.val; 
        (*newInstruction)->type_r->rt = instruction->arg2.val; 

        assemblyInstructions[assemblyCount++] = *newInstruction;

        (*newInstruction) = createAssemblyNode(typeR, "or");
        (*newInstruction)->type_r->rd = instruction->arg1.val; 
        (*newInstruction)->type_r->rs = $temp; 
        (*newInstruction)->type_r->rt = instruction->arg1.val;
    } else if (strcmp(instruction->operator, "LT") == 0) {
        *newInstruction = createAssemblyNode(typeR, "slt");
        (*newInstruction)->type_r->rd = instruction->arg1.val; 
        (*newInstruction)->type_r->rs = instruction->arg2.val; 
        (*newInstruction)->type_r->rt = instruction->arg3.val; 
    } else if (strcmp(instruction->operator, "GT") == 0) {
        *newInstruction = createAssemblyNode(typeR, "slt");
        (*newInstruction)->type_r->rd = instruction->arg1.val; 
        (*newInstruction)->type_r->rs = instruction->arg2.val; 
        (*newInstruction)->type_r->rt = instruction->arg3.val; 
    } else if (strcmp(instruction->operator, "GET") == 0) {
        *newInstruction = createAssemblyNode(typeR, "slt");
        (*newInstruction)->type_r->rd = instruction->arg1.val; 
        (*newInstruction)->type_r->rs = instruction->arg2.val; 
        (*newInstruction)->type_r->rt = instruction->arg3.val; 

        assemblyInstructions[assemblyCount++] = *newInstruction;

        rd = (*newInstruction)->type_r->rd;

        *newInstruction = createAssemblyNode(typeR, "xori");
        (*newInstruction)->type_r->rd = rd; 
        (*newInstruction)->type_r->rs = rd; 
        (*newInstruction)->type_r->rt = 1; 
    } else if (strcmp(instruction->operator, "LET") == 0) {
        *newInstruction = createAssemblyNode(typeR, "slt");
        (*newInstruction)->type_r->rd = instruction->arg1.val; 
        (*newInstruction)->type_r->rs = instruction->arg2.val; 
        (*newInstruction)->type_r->rt = instruction->arg3.val; 

        assemblyInstructions[assemblyCount++] = *newInstruction;

        rd = (*newInstruction)->type_r->rd;

        *newInstruction = createAssemblyNode(typeR, "xori");
        (*newInstruction)->type_r->rd = rd; 
        (*newInstruction)->type_r->rs = rd; 
        (*newInstruction)->type_r->rt = 1; 
    } else {
        return 0;
    }
    return 1;   
}


void generateAssembly(INSTRUCTION *instruction){
    ASSEMBLY * newInstruction = NULL;

    if (aritmeticOp(instruction, &newInstruction)){
        assemblyInstructions[assemblyCount++] = newInstruction;
    } else if (relationalOp(instruction, &newInstruction)){
        assemblyInstructions[assemblyCount++] = newInstruction;
    } 
}