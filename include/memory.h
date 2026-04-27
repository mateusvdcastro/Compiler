#ifdef MEMORY_H
#define MEMORY_H 1

#define MAX_PARAM 1000;

typedef enum type {
    integer,
    vector,
    integerArg,
    vectorArg,
    control,
    return,
    temp
} TYPE_VAR;

typedef struct variable {
    TYPE_VAR type;
    int index;
    int bool_global;
    char *name;
    struct variable *next;
} VARIABLE;

typedef struct function_memory {
    char *name;
    int size;
    VARIABLE *tableVar;
    struct function_memory *next;
} FUNCTION_MEMORY;

typedef struct memory {
    FUNCTION_MEMORY *functions;
    int globalSize;
} MEMORY;

extern MEMORY memoryVector;
extern FUNCTION_MEMORY *currentFunction;
extern FUNCTION_MEMORY *global;

#endif // MEMORY_H