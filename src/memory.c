#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "globals.h"
#include "memory.h"

FUNCTION_MEMORY *global = NULL; // Pointer to a global scope frame


void initializeMemory(MEMORY *memory) {
    FUNCTION_MEMORY *func_global;
    FUNCTION_MEMORY *parameters;
    if (memory == NULL) {
        return;
    }

    func_global = (FUNCTION_MEMORY *)malloc(sizeof(FUNCTION_MEMORY));
    if (func_global == NULL) {
        return;
    }

    func_global->size = 0;
    func_global->name = strdup("global");
    func_global->tableVar = NULL;
    func_global->next = NULL;

    global = func_global; // Set global to point to the global scope frame

    parameters = (FUNCTION_MEMORY *)malloc(sizeof(FUNCTION_MEMORY));
    if (parameters == NULL) {
        return;
    }
    
    parameters->size = 0;
    parameters->name = strdup("parameters");
    parameters->tableVar = NULL;
    parameters->next = NULL;

    global->next = parameters; // Link the parameters frame to the global frame

    memory->globalSize = 2; // Start with 2 frames: global and parameters
    memory->functions = func_global; 
}

void apagar_temp(FUNCTION_MEMORY* funcao){
    if(!funcao){
        printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);	
        printf("NULL passado como argumento em apagar_temp!\n");
        return;
    }

    VARIABLE* aux = funcao->tableVar;
    VARIABLE* aux2 = aux;
    
    // Caso nao tenha parametros
    if(funcao->size == 0){
        printf("Nao ha temporarios a serem apagados!\n");
        return;
    }

    // Caso so tenha um parametro
    if(funcao->size == 1){
        if(!strcmp(aux->name, "Param")){
            free(aux);
            funcao->size--;
            funcao->tableVar = NULL;
            return;
        }
    }

    // Caso tenha mais de um parametro
    while(aux->next != NULL){
        aux2 = aux;
        aux = aux->next;
    }

    if(!strcmp(aux->name, "Param")){
        free(aux);
        aux2->next = NULL;
        funcao->size--;
        return;
    }

    printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
    printf("Param's nao apagados!\n");
}


FUNCTION_MEMORY* insertFunction(MEMORY *memory, char *name) {
    if (memory == NULL || name == NULL) {
        return NULL;
    }

    FUNCTION_MEMORY *newFunc = (FUNCTION_MEMORY *)malloc(sizeof(FUNCTION_MEMORY));
    if (newFunc == NULL) {
        return NULL;
    }

    newFunc->size = 0;
    newFunc->name = strdup(name);
    newFunc->tableVar = NULL;
    newFunc->next = NULL;
    FUNCTION_MEMORY *aux = NULL;

    insertVariable(newFunc, "Control Link", control); // Control Link
    insertVariable(newFunc, "Return Address", ret_value); // Return Address
    insertVariable(newFunc, "Return Value", ret_value); // Return Value
    insertVariable(newFunc, "Temp Register", temp); // Temporary Register
    insertVariable(newFunc, "Register $fp", integer); // Frame Pointer Register
    insertVariable(newFunc, "Register $sp", integer); // Stack Pointer Register
    

    if (memory->globalSize == 0) {
        memory->functions = newFunc;
        memory->globalSize++;
        return newFunc;
    }

    aux = memory->functions;
    while (aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = newFunc;
    memory->globalSize++;

    return newFunc;
}

void insertVariable(FUNCTION_MEMORY *function, char *name, TYPE_VAR type) {
    if (function == NULL || name == NULL) {
        return;
    }

    VARIABLE *newVar = (VARIABLE *)malloc(sizeof(VARIABLE));
    if (newVar == NULL) {
        return;
    }

    newVar->type = type;
    newVar->index = function->size; // Use the current size as the index
    newVar->bool_global = (strcmp(function->name, "global") == 0) ? 1 : 0; // Mark as global if in global frame
    newVar->name = strdup(name);
    newVar->next = NULL;

    VARIABLE *aux = NULL;

    if (function->tableVar == NULL){
        function->tableVar = newVar;
        newVar->index = function->size;
        function->size++;
        return;
    }

    if (type == integerArg || type == vectorArg) {
        aux = function->tableVar;

        if (aux->type != integerArg && aux->type != vectorArg){
            newVar->next = function->tableVar;
            function->tableVar = newVar;
        } else {
            while (aux->next != NULL && (aux->next->type == integerArg || aux->next->type == vectorArg))
            {
                aux = aux->next;
            }
            
            VARIABLE * aux2 = aux->next;
    
            aux->next = newVar;
            newVar->next = aux2;
        }

        function->size++;
    
        aux = function->tableVar;
        for (int i = 0; aux != NULL; i++){
            aux->index = i;
            aux = aux->next;
        }
    
        return;
    }

    aux = function->tableVar;
    while (aux->next != NULL){
        aux = aux->next;
    }
    aux->next = newVar;
    newVar->index = function->size;
    function->size++;
}

VARIABLE * get_variable(FUNCTION_MEMORY * function, char * variableName){
    if (function == NULL){
        printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
        printf("NULL passado como argumento em get_variavel\n");
        return NULL;
    }

    FUNCTION_MEMORY* aux = function;

    VARIABLE* aux2 = NULL;
    while (aux!=NULL){
        aux2 = aux->tableVar;
        while(aux2 != NULL){
            if (strcmp(aux2->name, variableName) == 0){
                return aux2;
            }
            aux2 = aux2->next;
        }
        aux = aux->next;
    }

    aux = global;

    while (aux != NULL){
        aux2 = aux->tableVar;
        while (aux2 != NULL){
            if (strcmp(aux2->name, variableName) == 0){
                return aux2;
            }
            aux2 = aux2->next;
        }
        aux = aux->next;
    }

    printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
    printf("Variavel %s nao encontrada\n", variableName);

    return NULL;
}

FUNCTION_MEMORY* findFunction(MEMORY *memory, char *name) {
    if (memory == NULL || name == NULL) {
        return NULL;
    }

    FUNCTION_MEMORY *current = memory->functions;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current; // Function found
        }
        current = current->next;
    }

    printf("Erro: Função '%s' não encontrada na memória.\n", name);

    return NULL; // Function not found
}

int get_sp(FUNCTION_MEMORY *function) {
    if (function == NULL){
        printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
        printf("NULL passado como argumento em get_sp\n");
        return -1;
    }

    return function->size == 0 ? 0 : function->size - 1; // Return the index of the last variable, or 0 if no variables
}

int get_fp(FUNCTION_MEMORY *function) {
    if (function == NULL){
        printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
        printf("NULL passado como argumento em get_fp\n");
        return -1;
    }

    if (function == global) {
        return 0; // Global frame has no caller, so $fp is 0
    }

    return function->size; // Return the size of the function frame, which is the index for the next variable
}

int get_sp_relation(FUNCTION_MEMORY *function, VARIABLE *variable) {
    if (function == NULL || variable == NULL){
        printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
        printf("NULL passado como argumento em get_sp_relation\n");
        return -1;
    }

    return get_sp(function) - variable->index; // Calculate the offset from the current stack pointer to the variable
}

int get_fp_relation(FUNCTION_MEMORY *function, VARIABLE *variable) {
    if (function == NULL || variable == NULL){
        printf(ANSI_COLOR_RED); printf("Erro: "); printf(ANSI_COLOR_RESET);
        printf("NULL passado como argumento em get_fp_relation\n");
        return -1;
    }

    if (function == global) {
        return variable->index; // In the global frame, the variable index is the offset from $fp
    }

    return variable->index - get_fp(function); //
}

void printType(VARIABLE *variable) {
    switch (variable->type) {
        case integer:
            printf("INT");
            break;
        case integerArg:
            printf("INT_ARG");
            break;
        case vector:
            printf("VET");
            break;
        case vectorArg:
            printf("VET_ARG");
            break;
        case control:
            printf("CTRL");
            break;
        case ret_value:
            printf("RET");
            break;
        case temp:
            printf("TEMP");
            break;
        default:
            printf("UNKNOWN");
            break;
    }
}

void printMemory(){
    FUNCTION_MEMORY *aux = memoryVector.functions;
    VARIABLE *aux2 = NULL;

    for (int i = 0; i < memoryVector.globalSize; i++, aux = aux->next) {
        printf("===============================================\n");
        printf("\t\t%s: %d\n", aux->name, aux->size);
        printf("===============================================\n");

        int fp = get_fp(aux);
        int sp = get_sp(aux);
        int flag_sp = 0;
        aux2 = aux->tableVar;

        for (int j = 0; j < aux->size; j++, aux2 = aux2->next) {
            if (j == sp) {
                printf("SP -> ");
                flag_sp = 1;
            } else if (j == fp) {
                printf("FP -> ");
            } 

            printf("\t%d: %s [$fp + %d] [$sp - %d] : ",
                aux2->index, aux2->name, get_fp_relation(aux, aux2), get_sp_relation(aux, aux2));
            
            printType(aux2);
            aux2->bool_global ? printf(" (global)\n") : printf(" local\n");
            printf("\n");
        }

        if (!flag_sp && strcmp(aux->name, "global")) {
            printf("$sp -> \t%d:\n", sp);
        }

        flag_sp = 0;
    }
    printf("\n");
}

void freeMemory(){
    FUNCTION_MEMORY *aux = memoryVector.functions;
    FUNCTION_MEMORY *aux2 = aux;
    VARIABLE *auxVar = NULL;
    VARIABLE *auxVar2 = NULL;

    while (aux != NULL){
        auxVar = aux->tableVar;
        while (auxVar != NULL){
            auxVar2 = auxVar;
            auxVar = auxVar->next;
            free(auxVar2->name);
            free(auxVar2);
        }

        aux2 = aux;
        aux = aux->next;
        free(aux2->name);
        free(aux2);
    }
}




