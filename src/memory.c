#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

    insertVariable(newFunc, "Control Link", control); // Control Link
    insertVariable(newFunc, "Return Address", ret_value); // Return Address
    insertVariable(newFunc, "Return Value", ret_value); // Return Value
    insertVariable(newFunc, "Temp Register", temp); // Temporary Register
    insertVariable(newFunc, "Register $fp", integer); // Frame Pointer Register
    insertVariable(newFunc, "Register $sp", integer); // Stack Pointer Register
    

    // Insert the new function at the end of the linked list
    FUNCTION_MEMORY *current = memory->functions;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newFunc;

    memory->globalSize++; // Increment the count of function frames

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

    // Insert the new variable at the end of the variable list
    if (function->tableVar == NULL) {
        function->tableVar = newVar;
    } else {
        VARIABLE *current = function->tableVar;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newVar;
    }

    function->size++; // Increment the size of the function frame
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

void printMemory(){
    FUNCTION_MEMORY *currentFunc = memoryVector.functions;

    //TODO: Melhorar a formatação da impressão da memória com sp e fp
    while (currentFunc != NULL) {
        printf("Função: %s\n", currentFunc->name);
        VARIABLE *currentVar = currentFunc->tableVar;
        while (currentVar != NULL) {
            printf("  Variável: %s, Tipo: %d, Índice: %d, Global: %d\n", 
                currentVar->name, currentVar->type, currentVar->index, currentVar->bool_global);
            currentVar = currentVar->next;
        }
        currentFunc = currentFunc->next;
    }
}





