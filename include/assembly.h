#ifndef ASSEMBLY_H
#define ASSEMBLY_H 1

// Capacidade maxima para o vetor dos nomes das instrucoes
#define MAX_CHAR_NAME 5 /* Maximum characters in mnemonic */
#define MAX_ASSEMBLY 10000 /* Maximum number of assembly instructions */

#define $zero 31 // Sempre que eu precisar do valor 0, eu uso esse registrador, pois ele sempre tem o valor 0
#define $ra 30 // retorno de funcao Jump Register
#define $fp 29 // Frame Pointer (endereco do inicio da pilha de ativacao da funcao atual)
#define $sp 28 // Stack Pointer (endereco do topo da pilha de ativacao da funcao atual)
#define $temp 27 // Registrador para instruções que exigem registradores temporarios
#define $pilha 26 // Parametros da pilha (endereço das pilhas dos parametros)

typedef enum{
    typeR, // Instrucoes do tipo R
    typeI, // Instrucoes do tipo I
    typeJ, // Instrucoes do tipo J
    typeLabel // Label de funcoes ou de pulos
} instruction_type_t;

/* Struct para armazenar as informacoes
de instrucoes do tipo R */
typedef struct r_type{
    char *name; // Nome da instrucao
    int rd; // Registrador destino
    int rt; // Registrador fonte
    int rs; // Registrador fonte
    int shamt; // valor de Shift
} r_type_t;

/* Struct para armazenar as informacoes
de instrucoes do tipo I */
typedef struct i_type{
    char *name; // Nome da instrucao
    int rs; // Registrador fonte
    int rt; // Registrador destino
    int immediate; // Valor imediato
    int label; // Label para o branch
} i_type_t;

/* Struct para armazenar as informacoes 
de instrucoes do tipo J */
typedef struct j_type{
    char *name; // Nome da instrucao
    char *labelImmediate; // Nome da Label para o jump
} j_type_t;

typedef struct label_type{
    int is_dynamic; // Booleano para verificar se eh label(1) ou funcao(0)
    char *name; // Nome da label
    int endereco; // Endereco da label
} label_type_t;

typedef struct assembly{
    instruction_type_t type; // Tipo da instrucao
    i_type_t * type_i; // Ponteiro para a struct do tipo I
    r_type_t * type_r; // Ponteiro para a struct do tipo R
    j_type_t * type_j; // Ponteiro para a struct do tipo J
    label_type_t * type_label; // Ponteiro para a struct do tipo Label
} ASSEMBLY;

extern ASSEMBLY ** assemblyInstructions;
extern int assemblyCount;

void assembly();
void initializeAssembly();
ASSEMBLY * createAssemblyNode(instruction_type_t type, char *name);
void printAssembly();
void freeAssembly();

#endif