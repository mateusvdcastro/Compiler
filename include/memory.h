#ifndef MEMORY_H
#define MEMORY_H 1

#define MAX_PARAM 1000

typedef enum type {
    integer,
    vector,
    integerArg,
    vectorArg,
    control, // Andereço da variável que está afrente deve retornar um valor para a função que está abaixo na pilha de chamadas de função
    ret_value, // Valor de retorno de função
    temp // espaço para qualquer operação que precise
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

void initializeMemory(MEMORY *memory);
FUNCTION_MEMORY* insertFunction(MEMORY *memory, char *name);
void insertVariable(FUNCTION_MEMORY *function, char *name, TYPE_VAR type);
VARIABLE *get_variable(FUNCTION_MEMORY *function, char *variableName);
FUNCTION_MEMORY* findFunction(MEMORY *memory, char *name);
int get_fp(FUNCTION_MEMORY *function);
int get_sp(FUNCTION_MEMORY *function);
int get_fp_relation(FUNCTION_MEMORY *function, VARIABLE *variable);
int get_sp_relation(FUNCTION_MEMORY *function, VARIABLE *variable);
void freeMemory(void);
void printMemory();

#endif // MEMORY_H
