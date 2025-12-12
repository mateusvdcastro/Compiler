#ifndef _TABELA_SIMBOLOS_H_
#define _TABELA_SIMBOLOS_H_ 1

#include "globals.h"      /* define MAXLEXEME, declara variáveis globais */
#include "syntax_tree.h"  /* define StmtKind e typeType */

typedef struct NodeLine {
    int num_line;
    struct NodeLine *next;
    struct NodeLine *prev;
} NodeLine;

typedef struct item {
    char IDname[MAXLEXEME];
    char Scope[MAXLEXEME];
    StmtKind Statement;
    typeType DataType;
    NodeLine *lines;
    struct item *next;
    struct item *prev;
} Item;


//Cria uma tabela com valores neutros
Item **startable();

//Obtem o indice
unsigned int longhash(char *str);

//Adiciona uma linha na lista encadeada
void addline(Item *num, int line_value);

//Insere itens na tabela de simbolos
void insertable(Item *table[], StmtKind Statement, typeType DataType, char *name, char *scope, int line);

//Remove itens na tabela de simbolos
void removetable(Item *table[], Item *num);

//Procura itens na tabela de simbolos para a analise semântica de declarações
// Busca por ID dentro de um escopo (ou global). Parâmetros: tabela, ID, scope, tipo de declaração
Item *searchtable(Item *table[], char *ID, char *scope, StmtKind Statement);

//Free na tabela como um todo
void destructable(Item *table[]);

//Printa a tabela
void printable(Item *table[]);

// 
Item *searchtableExp(Item *table[], char id[], char scope[], ExpKind type_id);

//
Item *searchitemFunc(Item *table[], char *lexem);

//
Item *searchitemId(Item *table[], char *name);

//
Item *searchtableAny(Item *table[], char id[], char scope[]);

#endif 

