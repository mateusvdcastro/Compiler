#ifndef ASSEMBLY_H
#define ASSEMBLY_H 1

// Capacidade maxima para o vetor dos nomes das instrucoes
#define MAX_CHAR_NAME 5 /* Maximum characters in mnemonic */
#define MAX_ASSEMBLY 10000 /* Maximum number of assembly instructions */

#define $zero 31
#define $ra 30
#define $fp 29
#define $sp 28
#define $temp 27
#define $pilha 26
#define $s2 25
#define $s1 24
#define $s0 23
#define $temp2 22

typedef enum{
    typeR, // Instrucoes do tipo R
    typeI, // Instrucoes do tipo I
    typeJ, // Instrucoes do tipo J
    typeLabel // Label de funcoes ou de pulos
} instruction_type_t;

/* Struct para armazenar as informacoes
de instrucoes do tipo R */
typedef struct r_type{
    char *nome; // Nome da instrucao
    int rd; // Registrador destino
    int rt; // Registrador fonte
    int rs; // Registrador fonte
    int shamt; // valor de Shift
} r_type_t;

/* Struct para armazenar as informacoes
de instrucoes do tipo I */
typedef struct i_type{
    char *nome; // Nome da instrucao
    int rs; // Registrador fonte
    int rt; // Registrador destino
    int imediato; // Valor imediato
    int label; // Label para o branch
} i_type_t;

/* Struct para armazenar as informacoes 
de instrucoes do tipo J */
typedef struct j_type{
    char *nome; // Nome da instrucao
    char *labelImediato; // Nome da Label para o jump
} j_type_t;

typedef struct label_type{
    int is_dynamic; // Booleano para verificar se eh label(1) ou funcao(0)
    char *nome; // Nome da label
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
ASSEMBLY * createAssemblyNode(instruction_type_t type, char *nome);
void printAssembly();
void freeAssembly();

#endif