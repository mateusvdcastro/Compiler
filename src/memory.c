#include <stdlib.h>
#include <string.h>
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





