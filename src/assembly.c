#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codInterm.h"
#include "assembly.h"
#include "memory.h"
#include "label.h"

MEMORY memoryVector;
FUNCTION_MEMORY *currentFunction = NULL; // Pointer to the current function's memory frame
ASSEMBLY **assemblyInstructions = NULL;
int assemblyCount = 0;

const char * op_names[] = {
    "ADD", "SUB", "MULT", "DIV",
    "AND", "OR", "NOT",
    "EQ", "NEQ", "LT", "GT", "GET", "LET",
    "LOAD", "LOADI","STORE", "ASSIGN", "ALLOC", "ARG",
    "GOTO", "IFF", "PARAM", "CALL", "RET", "LABEL", "FUN",
};

void generateAssembly(INSTRUCTION *instruction);

static char *getLocalName(char *name) {
    char *separator;

    if (name == NULL) {
        return NULL;
    }

    separator = strstr(name, "::");
    if (separator != NULL) {
        return separator + 2;
    }

    return name;
}

static void formatLabelName(char *buffer, size_t size, int labelId) {
    if (buffer == NULL || size == 0) {
        return;
    }

    snprintf(buffer, size, "Label %d", labelId);
}

static int getFrameBaseRegister(VARIABLE *var) {
    return (var != NULL && var->bool_global) ? $zero : $fp;
}

void assembly (){
    initializeAssembly();

    for (int i = 0; i < intermediateCodeCount; i++){
        generateAssembly(intermediateCode[i]);
    }
}

void initializeAssembly(){
    assemblyInstructions = (ASSEMBLY **)malloc(MAX_ASSEMBLY * sizeof(ASSEMBLY *));

    for (int i = 0; i < MAX_ASSEMBLY; i++) {
        assemblyInstructions[i] = NULL;
    }

    assemblyCount = 0;

    initializeLabels();
    initializeMemory(&memoryVector);
    currentFunction = memoryVector.functions; // Start with the global scope
}

ASSEMBLY * createAssemblyNode(instruction_type_t type, char *name){
    ASSEMBLY * newNode = (ASSEMBLY *)malloc(sizeof(ASSEMBLY));
    newNode->type = type;
    newNode->type_i = NULL;
    newNode->type_r = NULL;
    newNode->type_j = NULL;
    newNode->type_label = NULL;

    switch (type) {
        case typeR:
            printf("Criando no de instrucao R: %s\n", name);
            newNode->type_r = (r_type_t *)malloc(sizeof(r_type_t));
            newNode->type_r->name = strdup(name);
            newNode->type_r->rd = -1;
            newNode->type_r->rs = -1;
            newNode->type_r->rt = -1;
            newNode->type_r->shamt = 0;
            break;
        case typeI:
            printf("Criando no de instrucao I: %s\n", name);
            newNode->type_i = (i_type_t *)malloc(sizeof(i_type_t));
            newNode->type_i->name = strdup(name);
            newNode->type_i->rs = -1;
            newNode->type_i->rt = -1;
            newNode->type_i->immediate = -1;
            newNode->type_i->label = -1;
            break;
        case typeJ:
            printf("Criando no de instrucao J: %s\n", name);
            newNode->type_j = (j_type_t *)malloc(sizeof(j_type_t));
            newNode->type_j->name = strdup(name);
            newNode->type_j->labelImmediate = NULL;
            break;
        case typeLabel:
            newNode->type_label = (label_type_t *)malloc(sizeof(label_type_t));
            newNode->type_label->name = strdup(name);
            newNode->type_label->is_dynamic = -1;
            newNode->type_label->endereco = -1;
            break;
    }

    return newNode;
}

int aritmeticOp(INSTRUCTION * instruction, ASSEMBLY ** newInstruction){
    if (strcmp(instruction->operator, "ADD") == 0) {
        *newInstruction = createAssemblyNode(typeR, "add");
        (*newInstruction)->type_r->rd = instruction->arg3->val;
        (*newInstruction)->type_r->rs = instruction->arg1->val;
        (*newInstruction)->type_r->rt = instruction->arg2->val;
    } else if (strcmp(instruction->operator, "SUB") == 0) {
        *newInstruction = createAssemblyNode(typeR, "sub");
        (*newInstruction)->type_r->rd = instruction->arg3->val;
        (*newInstruction)->type_r->rs = instruction->arg1->val;
        (*newInstruction)->type_r->rt = instruction->arg2->val;
    } else if (strcmp(instruction->operator, "MULT") == 0) {
        *newInstruction = createAssemblyNode(typeR, "mult");
        (*newInstruction)->type_r->rd = instruction->arg3->val;
        (*newInstruction)->type_r->rs = instruction->arg1->val;
        (*newInstruction)->type_r->rt = instruction->arg2->val;
    } else if (strcmp(instruction->operator, "DIV") == 0) {
        *newInstruction = createAssemblyNode(typeR, "div");
        (*newInstruction)->type_r->rd = instruction->arg3->val;
        (*newInstruction)->type_r->rs = instruction->arg1->val;
        (*newInstruction)->type_r->rt = instruction->arg2->val;
    } else if (strcmp(instruction->operator, "AND") == 0) {
        *newInstruction = createAssemblyNode(typeR, "and");
        (*newInstruction)->type_r->rd = instruction->arg3->val;
        (*newInstruction)->type_r->rs = instruction->arg1->val;
        (*newInstruction)->type_r->rt = instruction->arg2->val;
    } else if (strcmp(instruction->operator, "OR") == 0) {
        *newInstruction = createAssemblyNode(typeR, "or");
        (*newInstruction)->type_r->rd = instruction->arg3->val;
        (*newInstruction)->type_r->rs = instruction->arg1->val;
        (*newInstruction)->type_r->rt = instruction->arg2->val;
    } else {
        return 0;
    }
    return 1;
}

int relationalOp(INSTRUCTION * instruction, ASSEMBLY ** newInstruction){
    int rd;

    if (strcmp(instruction->operator, "EQ") == 0) {
        *newInstruction = createAssemblyNode(typeR, "xor");
        (*newInstruction)->type_r->rd = instruction->arg3->val;
        (*newInstruction)->type_r->rs = instruction->arg1->val;
        (*newInstruction)->type_r->rt = instruction->arg2->val;

        assemblyInstructions[assemblyCount++] = *newInstruction;

        (*newInstruction) = createAssemblyNode(typeI, "slti");
        (*newInstruction)->type_i->rt = instruction->arg3->val;
        (*newInstruction)->type_i->rs = instruction->arg3->val;
        (*newInstruction)->type_i->immediate = 1;
    } else if (strcmp(instruction->operator, "NEQ") == 0) {
        *newInstruction = createAssemblyNode(typeR, "slt");
        (*newInstruction)->type_r->rd = $temp;
        (*newInstruction)->type_r->rs = instruction->arg1->val;
        (*newInstruction)->type_r->rt = instruction->arg2->val;

        assemblyInstructions[assemblyCount++] = *newInstruction;

        (*newInstruction) = createAssemblyNode(typeR, "slt");
        (*newInstruction)->type_r->rd = instruction->arg3->val;
        (*newInstruction)->type_r->rs = instruction->arg2->val;
        (*newInstruction)->type_r->rt = instruction->arg1->val;

        assemblyInstructions[assemblyCount++] = *newInstruction;

        (*newInstruction) = createAssemblyNode(typeR, "or");
        (*newInstruction)->type_r->rd = instruction->arg3->val;
        (*newInstruction)->type_r->rs = $temp;
        (*newInstruction)->type_r->rt = instruction->arg3->val;
    } else if (strcmp(instruction->operator, "LT") == 0) {
        *newInstruction = createAssemblyNode(typeR, "slt");
        (*newInstruction)->type_r->rd = instruction->arg3->val;
        (*newInstruction)->type_r->rs = instruction->arg1->val;
        (*newInstruction)->type_r->rt = instruction->arg2->val;
    } else if (strcmp(instruction->operator, "GT") == 0) {
        *newInstruction = createAssemblyNode(typeR, "slt");
        (*newInstruction)->type_r->rd = instruction->arg3->val;
        (*newInstruction)->type_r->rs = instruction->arg2->val;
        (*newInstruction)->type_r->rt = instruction->arg1->val;
    } else if (strcmp(instruction->operator, "GET") == 0) {
        *newInstruction = createAssemblyNode(typeR, "slt");
        (*newInstruction)->type_r->rd = instruction->arg3->val;
        (*newInstruction)->type_r->rs = instruction->arg1->val;
        (*newInstruction)->type_r->rt = instruction->arg2->val;

        assemblyInstructions[assemblyCount++] = *newInstruction;

        rd = (*newInstruction)->type_r->rd;

        *newInstruction = createAssemblyNode(typeI, "xori");
        (*newInstruction)->type_i->rt = rd;
        (*newInstruction)->type_i->rs = rd;
        (*newInstruction)->type_i->immediate = 1;
    } else if (strcmp(instruction->operator, "LET") == 0) {
        *newInstruction = createAssemblyNode(typeR, "slt");
        (*newInstruction)->type_r->rd = instruction->arg3->val;
        (*newInstruction)->type_r->rs = instruction->arg2->val;
        (*newInstruction)->type_r->rt = instruction->arg1->val;

        assemblyInstructions[assemblyCount++] = *newInstruction;

        rd = (*newInstruction)->type_r->rd;

        *newInstruction = createAssemblyNode(typeI, "xori");
        (*newInstruction)->type_i->rt = rd;
        (*newInstruction)->type_i->rs = rd;
        (*newInstruction)->type_i->immediate = 1;
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
    } else if (!strcmp(instruction->operator, "ASSIGN")) {
        newInstruction = createAssemblyNode(typeR, "add");
        newInstruction->type_r->rd = instruction->arg1->val;
        newInstruction->type_r->rs = $zero;
        newInstruction->type_r->rt = instruction->arg2->val;
        assemblyInstructions[assemblyCount++] = newInstruction;
    } else if (!strcmp(instruction->operator, "LOADI")) {
        int aux_register = $zero;

        if (instruction->arg2->val > 0xFFFF){
            aux_register = instruction->arg1->val;

            newInstruction = createAssemblyNode(typeI, "ori");
            newInstruction->type_i->rt = instruction->arg1->val;
            newInstruction->type_i->rs = $zero;
            newInstruction->type_i->immediate = (instruction->arg2->val >> 16) & 0xFFFF;
            assemblyInstructions[assemblyCount++] = newInstruction;

            newInstruction = createAssemblyNode(typeR, "sll");
            newInstruction->type_r->rd = instruction->arg1->val;
            newInstruction->type_r->rs = instruction->arg1->val;
            newInstruction->type_r->rt = $zero;
            newInstruction->type_r->shamt = 16;
            assemblyInstructions[assemblyCount++] = newInstruction;
        }

        newInstruction = createAssemblyNode(typeI, "ori");
        newInstruction->type_i->rt = instruction->arg1->val;
        newInstruction->type_i->rs = aux_register;
        newInstruction->type_i->immediate = instruction->arg2->val & 0xFFFF;
        assemblyInstructions[assemblyCount++] = newInstruction;
    } else if (!strcmp(instruction->operator, "ALLOC")) {
        FUNCTION_MEMORY *func = findFunction(&memoryVector, instruction->arg2->name);

        if (func == NULL) {
            printf("Erro: Funcao %s nao encontrada para alocacao de variavel\n", instruction->arg2->name);
            return;
        }

        if (instruction->arg3->type == Empty){
            insertVariable(func, instruction->arg1->name, integer);
        } else {
            for (int i = 0; i < instruction->arg3->val; i++){
                insertVariable(func, instruction->arg1->name, vector);
            }
        }

        if (strcmp(func->name, "main") == 0){
            newInstruction = createAssemblyNode(typeI, "addi");
            newInstruction->type_i->rt = $sp;
            newInstruction->type_i->rs = $sp;
            newInstruction->type_i->immediate = instruction->arg3->type == Empty ? 1 : instruction->arg3->val;
            assemblyInstructions[assemblyCount++] = newInstruction;
        }
    } else if (!strcmp(instruction->operator, "LABEL")) {
        char labelName[32];

        formatLabelName(labelName, sizeof(labelName), instruction->arg1->val);
        newInstruction = createAssemblyNode(typeLabel, labelName);
        newInstruction->type_label->is_dynamic = 1;
        newInstruction->type_label->endereco = assemblyCount;

        insertLabel(labelName, assemblyCount);
        assemblyInstructions[assemblyCount++] = newInstruction;
    } else if (!strcmp(instruction->operator, "FUN")){
        char *functionName = instruction->arg2->name;

        if (functionName == NULL) {
            return;
        }

        printf("Gerando codigo para funcao: %s\n", functionName);
        newInstruction = createAssemblyNode(typeLabel, functionName);
        newInstruction->type_label->is_dynamic = 0;
        insertLabel(functionName, assemblyCount);
        assemblyInstructions[assemblyCount++] = newInstruction;

        currentFunction = insertFunction(&memoryVector, functionName);

        if (!strcmp(functionName, "main")){
            newInstruction = createAssemblyNode(typeI, "ori");
            newInstruction->type_i->rt = $fp;
            newInstruction->type_i->rs = $zero;
            newInstruction->type_i->immediate = findFunction(&memoryVector, "global")->size + get_fp(currentFunction);
            assemblyInstructions[assemblyCount++] = newInstruction;

            newInstruction = createAssemblyNode(typeR, "add");
            newInstruction->type_r->rd = $fp;
            newInstruction->type_r->rs = $fp;
            newInstruction->type_r->rt = $zero;
            assemblyInstructions[assemblyCount++] = newInstruction;

            newInstruction = createAssemblyNode(typeI, "ori");
            newInstruction->type_i->rt = $sp;
            newInstruction->type_i->rs = $zero;
            newInstruction->type_i->immediate = findFunction(&memoryVector, "global")->size + get_sp(currentFunction);
            assemblyInstructions[assemblyCount++] = newInstruction;

            newInstruction = createAssemblyNode(typeR, "add");
            newInstruction->type_r->rd = $sp;
            newInstruction->type_r->rs = $sp;
            newInstruction->type_r->rt = $zero;
            assemblyInstructions[assemblyCount++] = newInstruction;

            newInstruction = createAssemblyNode(typeI, "addi");
            newInstruction->type_i->rt = $pilha;
            newInstruction->type_i->rs = $zero;
            newInstruction->type_i->immediate = 4000;
            assemblyInstructions[assemblyCount++] = newInstruction;
        } else {
            newInstruction = createAssemblyNode(typeI, "sw");
            newInstruction->type_i->rt = $ra;
            newInstruction->type_i->rs = $fp;
            newInstruction->type_i->immediate = get_fp_relation(currentFunction, get_variable(currentFunction, "Return Address")) + instruction->arg3->val;
            assemblyInstructions[assemblyCount++] = newInstruction;
        }
    } else if (!strcmp(instruction->operator, "ARG")){
        FUNCTION_MEMORY *currentFunc = findFunction(&memoryVector, instruction->arg3->name);

        if (currentFunc == NULL) {
            return;
        }

        if (!strcmp(instruction->arg1->name, "INT")){
            printf("Inserindo variavel de argumento: %s do tipo INT na funcao %s\n", instruction->arg2->name, currentFunc->name);
            insertVariable(currentFunc, instruction->arg2->name, integerArg);
        } else {
            insertVariable(currentFunc, instruction->arg2->name, vectorArg);
        }

        if (strcmp(currentFunc->name, "main") == 0){
            newInstruction = createAssemblyNode(typeI, "addi");
            newInstruction->type_i->rt = $sp;
            newInstruction->type_i->rs = $sp;
            newInstruction->type_i->immediate = 1;
            assemblyInstructions[assemblyCount++] = newInstruction;
        }
    } else if (!strcmp(instruction->operator, "LOAD")){
        char *variableName = getLocalName(instruction->arg2->name);
        VARIABLE *var = get_variable(currentFunction, variableName);
        int baseRegister;

        if (var == NULL) {
            return;
        }

        baseRegister = getFrameBaseRegister(var);

        if (instruction->arg3 != NULL && instruction->arg3->type != Empty) {
            if (var->type == vectorArg) {
                newInstruction = createAssemblyNode(typeI, "lw");
                newInstruction->type_i->rt = $temp;
                newInstruction->type_i->rs = $fp;
                newInstruction->type_i->immediate = get_fp_relation(currentFunction, var);
                assemblyInstructions[assemblyCount++] = newInstruction;
            } else {
                newInstruction = createAssemblyNode(typeI, "addi");
                newInstruction->type_i->rt = $temp;
                newInstruction->type_i->rs = baseRegister;
                newInstruction->type_i->immediate = get_fp_relation(currentFunction, var);
                assemblyInstructions[assemblyCount++] = newInstruction;
            }

            newInstruction = createAssemblyNode(typeR, "add");
            newInstruction->type_r->rd = $temp;
            newInstruction->type_r->rs = $temp;
            newInstruction->type_r->rt = instruction->arg3->val;
            assemblyInstructions[assemblyCount++] = newInstruction;

            newInstruction = createAssemblyNode(typeI, "lw");
            newInstruction->type_i->rt = instruction->arg1->val;
            newInstruction->type_i->rs = $temp;
            newInstruction->type_i->immediate = 0;
            assemblyInstructions[assemblyCount++] = newInstruction;
        } else {
            newInstruction = createAssemblyNode(typeI, "lw");
            newInstruction->type_i->rt = instruction->arg1->val;
            newInstruction->type_i->rs = baseRegister;
            newInstruction->type_i->immediate = get_fp_relation(currentFunction, var);
            assemblyInstructions[assemblyCount++] = newInstruction;
        }
    } else if (!strcmp(instruction->operator, "PARAM")){
        FUNCTION_MEMORY *parameters = findFunction(&memoryVector, "parameters");

        if (parameters == NULL) {
            return;
        }

        if (instruction->arg2->type == String && !strcmp(instruction->arg2->name, "VET")) {
            VARIABLE *var = get_variable(currentFunction, getLocalName(instruction->arg3->name));
            int baseRegister;

            if (var == NULL) {
                return;
            }

            baseRegister = getFrameBaseRegister(var);

            if (var->type == vectorArg) {
                newInstruction = createAssemblyNode(typeI, "lw");
                newInstruction->type_i->rt = instruction->arg1->val;
                newInstruction->type_i->rs = $fp;
                newInstruction->type_i->immediate = get_fp_relation(currentFunction, var);
                assemblyInstructions[assemblyCount++] = newInstruction;
            } else {
                newInstruction = createAssemblyNode(typeI, "addi");
                newInstruction->type_i->rt = instruction->arg1->val;
                newInstruction->type_i->rs = baseRegister;
                newInstruction->type_i->immediate = get_fp_relation(currentFunction, var);
                assemblyInstructions[assemblyCount++] = newInstruction;
            }
        }

        newInstruction = createAssemblyNode(typeI, "sw");
        newInstruction->type_i->rt = instruction->arg1->val;
        newInstruction->type_i->rs = $pilha;
        newInstruction->type_i->immediate = parameters->size;
        assemblyInstructions[assemblyCount++] = newInstruction;

        insertVariable(parameters, "Param", temp);
    } else if (!strcmp(instruction->operator, "RET")){
        if (instruction->arg1->type == Empty) {
            return;
        }

        newInstruction = createAssemblyNode(typeI, "lw");
        newInstruction->type_i->rt = $temp;
        newInstruction->type_i->rs = $fp;
        newInstruction->type_i->immediate = get_fp_relation(currentFunction, get_variable(currentFunction, "Control Link"));
        assemblyInstructions[assemblyCount++] = newInstruction;

        newInstruction = createAssemblyNode(typeI, "sw");
        newInstruction->type_i->rt = instruction->arg1->val;
        newInstruction->type_i->rs = $temp;
        newInstruction->type_i->immediate = 2;
        assemblyInstructions[assemblyCount++] = newInstruction;
    } else if (!strcmp(instruction->operator, "IFF")){
        newInstruction = createAssemblyNode(typeI, "beq");
        newInstruction->type_i->rs = $zero;
        newInstruction->type_i->rt = instruction->arg1->val;
        newInstruction->type_i->label = instruction->arg2->val;
        assemblyInstructions[assemblyCount++] = newInstruction;
    } else if (!strcmp(instruction->operator, "GOTO")){
        char labelName[32];
        const char *targetName;

        if (instruction->arg1->type == String && instruction->arg1->name != NULL) {
            targetName = instruction->arg1->name;
        } else {
            formatLabelName(labelName, sizeof(labelName), instruction->arg1->val);
            targetName = labelName;
        }

        newInstruction = createAssemblyNode(typeJ, "j");
        newInstruction->type_j->labelImmediate = strdup(targetName);
        assemblyInstructions[assemblyCount++] = newInstruction;

    } else if (!strcmp(instruction->operator, "HALT")){
        newInstruction = createAssemblyNode(typeJ, "halt");
        newInstruction->type_j->labelImmediate = strdup("$zero");
        assemblyInstructions[assemblyCount++] = newInstruction;
    } else if (!strcmp(instruction->operator, "STORE")) {
        if (!instruction->arg3){
            return;
        }

        char *variableName = getLocalName(instruction->arg1->name);
        VARIABLE *var = get_variable(currentFunction, variableName);
        int baseRegister;

        if (var == NULL) {
            return;
        }

        baseRegister = getFrameBaseRegister(var);

        if (instruction->arg3->type != Empty){
            //Store de um valor em um vetor

            if (var->type == vectorArg){
                newInstruction = createAssemblyNode(typeI, "lw");
                newInstruction->type_i->rt = $temp;
                newInstruction->type_i->rs = $fp;
                newInstruction->type_i->immediate = get_fp_relation(currentFunction, var);
                assemblyInstructions[assemblyCount++] = newInstruction;
            } else {
                newInstruction = createAssemblyNode(typeI, "addi");
                newInstruction->type_i->rt = $temp;
                newInstruction->type_i->rs = baseRegister;
                newInstruction->type_i->immediate = get_fp_relation(currentFunction, var);
                assemblyInstructions[assemblyCount++] = newInstruction;
            }

            newInstruction = createAssemblyNode(typeR, "add");
            newInstruction->type_r->rd = $temp;
            newInstruction->type_r->rs = $temp;
            newInstruction->type_r->rt = instruction->arg3->val;
            assemblyInstructions[assemblyCount++] = newInstruction;

            newInstruction = createAssemblyNode(typeI, "sw");
            newInstruction->type_i->rt = instruction->arg2->val;
            newInstruction->type_i->rs = $temp;
            newInstruction->type_i->immediate = 0;
            assemblyInstructions[assemblyCount++] = newInstruction;
        } else {
            //Store de um valor em uma variavel

            newInstruction = createAssemblyNode(typeI, "sw");
            newInstruction->type_i->rt = instruction->arg2->val;
            newInstruction->type_i->rs = baseRegister;
            newInstruction->type_i->immediate = get_fp_relation(currentFunction, var);
            assemblyInstructions[assemblyCount++] = newInstruction;
        }
    } else if (!strcmp(instruction->operator, "CALL")){
        if (!instruction->arg3){
            printf("Erro: Chamada sem registrador de destino.\n");
            return;
        }

        if (!strcmp(instruction->arg1->name, "output")){
            delete_temp(findFunction(&memoryVector, "parameters"));

            newInstruction = createAssemblyNode(typeI, "lw");
            newInstruction->type_i->rt = $temp;
            newInstruction->type_i->rs = $pilha;
            newInstruction->type_i->immediate = findFunction(&memoryVector, "parameters")->size;
            assemblyInstructions[assemblyCount++] = newInstruction;

            newInstruction = createAssemblyNode(typeI, "out");
            newInstruction->type_i->rt = $temp;
            newInstruction->type_i->rs = $zero;
            newInstruction->type_i->immediate = 0;
            assemblyInstructions[assemblyCount++] = newInstruction;

            return;
        }
        if (!strcmp(instruction->arg1->name, "input")){
            newInstruction = createAssemblyNode(typeI, "in");
            newInstruction->type_i->rt = instruction->arg3->val;
            newInstruction->type_i->rs = $zero;
            newInstruction->type_i->immediate = 0;
            assemblyInstructions[assemblyCount++] = newInstruction;

            return;
        }

        for (int i = instruction->arg2->val; i > 0; i--){

            delete_temp(findFunction(&memoryVector, "parameters"));

            newInstruction = createAssemblyNode(typeI, "lw");
            newInstruction->type_i->rt = $temp;
            newInstruction->type_i->rs = $pilha;
            newInstruction->type_i->immediate = findFunction(&memoryVector, "parameters")->size;
            assemblyInstructions[assemblyCount++] = newInstruction;

            newInstruction = createAssemblyNode(typeI, "sw");
            newInstruction->type_i->rt = $temp;
            newInstruction->type_i->rs = $sp;
            newInstruction->type_i->immediate = i;
            assemblyInstructions[assemblyCount++] = newInstruction;
        }

        newInstruction = createAssemblyNode(typeR, "add");
        newInstruction->type_r->rt = $zero;
        newInstruction->type_r->rs = $fp;
        newInstruction->type_r->rd = $temp;
        assemblyInstructions[assemblyCount++] = newInstruction;

        newInstruction = createAssemblyNode(typeI, "addi");
        newInstruction->type_i->rt = $temp;
        newInstruction->type_i->rs = $temp;
        newInstruction->type_i->immediate = get_fp_relation(currentFunction, get_variable(currentFunction, "Control Link"));
        assemblyInstructions[assemblyCount++] = newInstruction;

        newInstruction = createAssemblyNode(typeI, "sw");
        newInstruction->type_i->rt = $temp;
        newInstruction->type_i->rs = $sp;
        newInstruction->type_i->immediate = instruction->arg2->val + 1;
        assemblyInstructions[assemblyCount++] = newInstruction;

        newInstruction = createAssemblyNode(typeI, "addi");
        newInstruction->type_i->rt = $fp;
        newInstruction->type_i->rs = $fp;
        newInstruction->type_i->immediate = get_sp(currentFunction) + 1;
        assemblyInstructions[assemblyCount++] = newInstruction;

        FUNCTION_MEMORY *calledFunc = findFunction(&memoryVector, instruction->arg1->name);

        newInstruction = createAssemblyNode(typeI, "addi");
        newInstruction->type_i->rt = $sp;
        newInstruction->type_i->rs = $sp;
        newInstruction->type_i->immediate = get_sp(calledFunc) + 1;
        assemblyInstructions[assemblyCount++] = newInstruction;

        newInstruction = createAssemblyNode(typeJ, "jal");
        newInstruction->type_j->labelImmediate = strdup(instruction->arg1->name);
        assemblyInstructions[assemblyCount++] = newInstruction;

        newInstruction = createAssemblyNode(typeI, "subi");
        newInstruction->type_i->rt = $fp;
        newInstruction->type_i->rs = $fp;
        newInstruction->type_i->immediate = get_sp(currentFunction) + 1;
        assemblyInstructions[assemblyCount++] = newInstruction;

        newInstruction = createAssemblyNode(typeI, "subi");
        newInstruction->type_i->rt = $sp;
        newInstruction->type_i->rs = $sp;
        newInstruction->type_i->immediate = get_sp(calledFunc) + 1;
        assemblyInstructions[assemblyCount++] = newInstruction;

        if (instruction->arg3->type != Empty){
            newInstruction = createAssemblyNode(typeI, "lw");
            newInstruction->type_i->rt = instruction->arg3->val;
            newInstruction->type_i->rs = $fp;
            newInstruction->type_i->immediate = get_fp_relation(currentFunction, get_variable(currentFunction, "Return Value"));
            assemblyInstructions[assemblyCount++] = newInstruction;
        }
    } else if (!strcmp(instruction->operator, "END")){
        if (!strcmp(instruction->arg1->name,"main")){
            return;
        }

        newInstruction = createAssemblyNode(typeI, "lw");
        newInstruction->type_i->rs = $fp;
        newInstruction->type_i->rt = $ra;
        newInstruction->type_i->immediate = get_fp_relation(currentFunction, get_variable(currentFunction, "Return Address"));
        assemblyInstructions[assemblyCount++] = newInstruction;

        newInstruction = createAssemblyNode(typeR, "jr");
        newInstruction->type_r->rs = $ra;
        newInstruction->type_r->rd = $zero;
        newInstruction->type_r->rt = $zero;
        assemblyInstructions[assemblyCount++] = newInstruction;
    } else {
        printf("Operacao '%s' nao implementada na geracao de codigo de montagem.\n", instruction->operator);
    }
}

void type_reg(int reg){
    switch (reg){
        case $zero:
            fprintf(outputFile_Assembly, "$zero");
            break;
        case $ra:
            fprintf(outputFile_Assembly, "$ra");
            break;
        case $fp:
            fprintf(outputFile_Assembly, "$fp");
            break;
        case $sp:
            fprintf(outputFile_Assembly, "$sp");
            break;
        case $temp:
            fprintf(outputFile_Assembly, "$temp");
            break;
        case $pilha:
            fprintf(outputFile_Assembly, "$pilha");
            break;
        default:
            fprintf(outputFile_Assembly, "$t%d", reg);
            break;
    }
}

void printAssembly(){
    i_type_t * type_i = NULL;
    r_type_t * type_r = NULL;
    j_type_t * type_j = NULL;
    label_type_t * type_label = NULL;

    fprintf(outputFile_Assembly, "============== Assembly ============== \n");

    for (int i = 0; i < assemblyCount; i++){
        fprintf(outputFile_Assembly, "%d: ", i);
        if (i<10)
            fprintf(outputFile_Assembly, " ");
        if (assemblyInstructions[i]->type == typeI){
            type_i = assemblyInstructions[i]->type_i;
            fprintf(outputFile_Assembly, "\t%s ", type_i->name);
            type_reg(type_i->rt);
            fprintf(outputFile_Assembly, " ");

            if (!strcmp(type_i->name, "lw") || !strcmp(type_i->name, "sw")){
                fprintf(outputFile_Assembly, "%d(", type_i->immediate);
                type_reg(type_i->rs);
                fprintf(outputFile_Assembly, ")\n");
            } else {
                type_reg(type_i->rs);
                fprintf(outputFile_Assembly, " ");
                if (type_i->label != -1) fprintf(outputFile_Assembly, "Label %d\n", type_i->label);
                else fprintf(outputFile_Assembly, "%d\n", type_i->immediate);
            }
        }
        else if (assemblyInstructions[i]->type == typeR){
            type_r = assemblyInstructions[i]->type_r;
            fprintf(outputFile_Assembly, "\t%s ", type_r->name);
            type_reg(type_r->rd);
            fprintf(outputFile_Assembly, " ");
            type_reg(type_r->rs);
            fprintf(outputFile_Assembly, " ");
            type_reg(type_r->rt);
            fprintf(outputFile_Assembly, "\n");
        }
        else if (assemblyInstructions[i]->type == typeJ){
            type_j = assemblyInstructions[i]->type_j;
            fprintf(outputFile_Assembly, "\t%s ", type_j->name);
            if (type_j->labelImmediate != NULL) {
                fprintf(outputFile_Assembly, "%s\n", type_j->labelImmediate);
            } else {
                fprintf(outputFile_Assembly, "\n");
            }
        }
        else if (assemblyInstructions[i]->type == typeLabel){
            type_label = assemblyInstructions[i]->type_label;
            fprintf(outputFile_Assembly, "%s:\n", type_label->name);
        }
    }
}
