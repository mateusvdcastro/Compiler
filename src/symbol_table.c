#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_simbolos.h"

#define MAX 211

//Cria uma tabela com valores zerados
Item **startable() {
    Item **table = (Item **)calloc(MAX, sizeof(Item*));    
    return table;
}

//Calcula o indice por hash
unsigned int longhash(char *str){
    unsigned long hash = 0; 
    unsigned long alpha = 1;
    unsigned int idx;
    char c;
    int i;
    for(i = strlen(str)-1; i >= 0; i--){
        c = str[i];
        hash += alpha*c;
        alpha = ((alpha << 4));
    }

    idx = hash % MAX;

    return idx;
}

//
void addline(Item *num, int line_value){
    if(num == NULL) return;

    NodeLine *new = (NodeLine*)calloc(1, sizeof(NodeLine));
    if(new == NULL) return;  /* falha de alocação */

    new->num_line = line_value;
    new->next = NULL;
    new->prev = NULL;

    NodeLine *aux = num->lines;

    if(aux == NULL){
        num->lines = new;
        return; 
    }  

    while(aux->next != NULL){
        aux = aux->next;
    }

    aux->next = new;
    new->prev = aux;
}

void insertable(Item *table[], StmtKind Statement, typeType DataType, char *name, char *scope, int line){
    insertableWithParams(table, Statement, DataType, name, scope, line, 0);
}

void insertableWithParams(Item *table[], StmtKind Statement, typeType DataType, char *name, char *scope, int line, int paramCount){
    unsigned int idx = longhash(name);

    /* Se já existe um identificador com mesmo nome e mesmo escopo (ou escopo global),
       apenas adiciona a linha de ocorrência e retorna, evitando inserir duplicata. */
    if(table != NULL && name != NULL && scope != NULL) {
        Item *aux = table[idx];
        while(aux != NULL) {
            if(strcmp(name, aux->IDname) == 0 &&
               (strcmp(scope, aux->Scope) == 0 || strcmp(aux->Scope, "global") == 0)) {
                addline(aux, line);
                return; /* já presente, não inserir novo item */
            }
            aux = aux->next;
        }
    }

    Item *new = (Item *)calloc(1, sizeof(Item));
    if(new == NULL) return;

    /* copia segura das strings para os arrays em Item */
    strncpy(new->IDname, name, MAXLEXEME-1);
    new->IDname[MAXLEXEME-1] = '\0';
    strncpy(new->Scope, scope, MAXLEXEME-1);
    new->Scope[MAXLEXEME-1] = '\0';

    new->Statement = Statement;
    new->DataType  = DataType;
    new->paramCount = paramCount;
    new->paramKinds = NULL;
    new->lines     = NULL;

    /* adiciona linha de ocorrência */
    addline(new, line);

    /* inserção no início da lista (trata colisão) */
    new->prev = NULL;
    new->next = table[idx];

    if(table[idx] != NULL){
        table[idx]->prev = new;
    }

    table[idx] = new;
}


void removetable(Item *table[], Item *num){
    if(num == NULL) return;

    unsigned int idx = longhash(num->IDname);

    /* Caso 1: nó é o primeiro da lista */
    if(table[idx] == num){
        table[idx] = num->next;

        if(num->next != NULL){
            num->next->prev = NULL;
        }
    }
    /* Caso 2: nó está no meio ou no fim */
    else{
        if(num->prev != NULL){
            num->prev->next = num->next;
        }

        if(num->next != NULL){
            num->next->prev = num->prev;
        }
    }

    /* desconecta completamente */
    num->next = NULL;
    num->prev = NULL;


    NodeLine *ln = num->lines;
    while(ln){
        NodeLine *tmp = ln->next;
        free(ln);
        ln = tmp;
    }

    if (num->paramKinds) {
        free(num->paramKinds);
        num->paramKinds = NULL;
    }

    free(num);
}


Item *searchtable(Item *table[], char *ID, char *scope, StmtKind Statement){
   
    unsigned int idx = longhash(ID);
    Item *aux = table[idx];

    if(Statement == FunDeclK){
        while(aux != NULL){
            if(strcmp(ID, aux->IDname) == 0){
                return aux;
            }
            aux = aux->next;
        }
        return NULL;
    }

    while(aux != NULL){
        if(strcmp(ID, aux->IDname) == 0){

            if(strcmp(scope, aux->Scope) == 0 ||
               strcmp(aux->Scope, "global") == 0){
                return aux;
            }

            if(aux->Statement == FunDeclK){
                return aux;
            }
        }
        aux = aux->next;
    }

    return NULL;
}

void destructable(Item *table[]){
    Item *item;
    Item *nextItem;
    NodeLine *line;
    NodeLine *nextLine;

    if(table == NULL) return;

    for(int i = 0; i < MAX; i++){
        item = table[i];

        while(item != NULL){
            /* guarda próximo item antes de liberar */
            nextItem = item->next;

            /* libera lista de linhas (uma única vez) */
            line = item->lines;
            while(line != NULL){
                nextLine = line->next;
                free(line);
                line = nextLine;
            }

            /* libera item (strings são arrays fixos em Item, não devem ser free()) */
            if (item->paramKinds) free(item->paramKinds);
            free(item);

            item = nextItem;
        }

        table[i] = NULL;
    }

    free(table);
}

/* Converter StmtKind para string */
static const char *stmtKindToString(StmtKind kind) {
    switch(kind) {
        case VarDeclK:    return "VarDecl";
        case VetDeclK:    return "ArrayDecl";
        case FunDeclK:    return "FunDecl";
        case ParamVoid:   return "ParamVoid";
        case VarParamK:   return "VarParam";
        case VetParamK:   return "ArrayParam";
        case CompK:       return "Compound";
        case IfK:         return "If";
        case WhileK:      return "While";
        case ReturnInK:   return "ReturnInt";
        case ReturnVoidK: return "ReturnVoid";
        case CallK:       return "Call";
        default:          return "Unknown";
    }
}

/* Converter typeType para string */
static const char *typeTypeToString(typeType type) {
    switch(type) {
        case Type_int:  return "int";
        case Type_void: return "void";
        default:        return "unknown";
    }
}

/* Imprime a tabela de símbolos de forma apresentável */
void printable(Item *table[]) {
    if(table == NULL) return;

    Item *aux = NULL;
    NodeLine *auxLines = NULL;

    printf("\n============== TABELA DE SÍMBOLOS ==============\n\n");

    for(int i = 0; i < MAX; i++) {
        if(table[i] != NULL) {
            aux = table[i];
            while(aux != NULL) {
                printf("Nome: %s\n", aux->IDname);
                
                if(aux->Statement != FunDeclK)
                    printf("Escopo: %s\n", aux->Scope);
            
                if(aux->DataType == Type_int) {
                    printf("Tipo de dado: INT\n");
                }
                else {
                    printf("Tipo de dado: VOID\n");
                }
                
                if(aux->Statement == VarDeclK) {
                    printf("Tipo de identificador: VAR\n");
                }
                else if(aux->Statement == FunDeclK) {
                    printf("Tipo de identificador: FUN\n");
                }
                else if(aux->Statement == VetDeclK) {
                    printf("Tipo de identificador: VET\n");
                }
                else {
                    printf("Tipo de identificador: PARAM\n");
                }

                printf("Linhas: ");
                auxLines = aux->lines;
                while(auxLines != NULL) {
                    printf("%d ", auxLines->num_line);
                    auxLines = auxLines->next;
                }
                printf("\n\n");
                aux = aux->next;
            }
        }
    }

    printf("================================================\n\n");
}

/* Busca por ID em contexto de expressão */
Item *searchtableExp(Item* table[], char id[], char scope[], ExpKind type_id) {
    if(table == NULL) return NULL;
    
    unsigned int idx = longhash(id);
    Item *aux = table[idx];
    
    while(aux != NULL) {
        if(strcmp(id, aux->IDname) == 0) {
            if(strcmp(scope, aux->Scope) == 0 || strcmp(aux->Scope, "global") == 0) {
                return aux;
            }
        }
        aux = aux->next;
    }
    
    return NULL;
}

/* Busca por identificador de função pelo lexema: percorre todas as buckets */
Item *searchitemFunc(Item *table[], char *lexem) {
    if(table == NULL || lexem == NULL) return NULL;

    for(int i = 0; i < MAX; i++){
        Item *item = table[i];
        while(item != NULL){
            if(item->Statement == FunDeclK && strcmp(item->IDname, lexem) == 0){
                return item;
            }
            item = item->next;
        }
    }

    return NULL;
}

/* Busca por identificador simples por nome (sem escopo) */
Item *searchitemId(Item *table[], char *name) {
    if(table == NULL || name == NULL) return NULL;
    
    unsigned int idx = longhash(name);
    Item *aux = table[idx];
    
    while(aux != NULL) {
        if(strcmp(name, aux->IDname) == 0) {
            return aux;
        }
        aux = aux->next;
    }
    
    return NULL;
}

/* Busca genérica por ID e escopo (sem considerar tipo de declaração) */
Item *searchtableAny(Item *table[], char id[], char scope[]) {
    if(table == NULL || id == NULL || scope == NULL) return NULL;
    
    unsigned int idx = longhash(id);
    Item *aux = table[idx];
    
    while(aux != NULL) {
        if(strcmp(id, aux->IDname) == 0) {
            /* busca por escopo exato ou global */
            if(strcmp(scope, aux->Scope) == 0 || strcmp(aux->Scope, "global") == 0) {
                return aux;
            }
        }
        aux = aux->next;
    }
    
    return NULL;
}