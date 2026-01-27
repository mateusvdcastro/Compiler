#ifndef _ANALISE_SEMANT_H_
#define _ANALISE_SEMANT_H_ 1

#include "syntax_tree.h"
#include "tabela_simbolos.h"

typedef enum {
    ErrVoidVarDecl,        // Variável declarada como void
    ErrFuncRedecl,         // Função declarada mais de uma vez
    ErrVarRedecl,          // Variável declarada mais de uma vez
    ErrFuncAsVar,          // Função declarada com nome de variável
    ErrVarAsFunc,          // Variável declarada com nome de função
    ErrVarUndeclared,      // Variável usada sem declaração
    ErrFuncUndeclared,     // Função usada sem declaração
    ErrAssignVoidFunc,     // Função void atribuída a variável
    ErrMainMissing,        // Função main não declarada
    ErrVectorUndeclared,   // Vetor usado sem declaração
    ErrFuncCallMissingPar  // Chamada de função sem "()"
    , ErrReturnValueInVoid  // Retorno com valor em função void
    , ErrReturnVoidInNonVoid // Retorno sem valor em função não-void
    , ErrWrongArgCount      // Número errado de argumentos na chamada
    , ErrArrayArgMismatch   // Argumento de vetor inválido para parâmetro de vetor
    , ErrNegativeIndex      // Índice negativo em matriz
} SemanticError;

// Estrutura interna para rastrear o tipo de função atual durante análise
typedef struct {
    char funcName[MAXLEXEME];
    typeType returnType;  // Type_int ou Type_void
    int paramCount;       // Número de parâmetros esperados
    int hasReturn;        // Flag: se função possui algum return
    int hasReturnValue;   // Flag: se função int tem return com valor
} FunctionContext;

extern int semanticError;


int countFunctionParams(TreeNode *paramNode);
void analyzeStmt(TreeNode *syntaxTree, Item *symbolTable[], char *scope);
void analyzeExp(TreeNode *syntaxTree, Item *symbolTable[], char *scope);
void analyzeTree(TreeNode *syntaxTree, Item *symbolTable[], char *scope);
int searchEqual(Item *symbolTable[], TreeNode *syntaxTree, int index, char *scope);
void showSemanticError(SemanticError error, char *name, int line);

/* Final checks executed after full traversal (ex.: verificar main) */
void finalizeSemanticChecks(TreeNode *tree, Item *symbolTable[]);
void verifyIntFunctionsReturn(TreeNode *tree);
void checkForReturnValue(TreeNode *tree);
int checkForAnyReturn(TreeNode *tree);

#endif