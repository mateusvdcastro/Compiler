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
} SemanticError;

extern int semanticError;


void analyzeStmt(TreeNode *syntaxTree, Item *symbolTable[], char *scope);
void analyzeExp(TreeNode *syntaxTree, Item *symbolTable[], char *scope);
void analyzeTree(TreeNode *syntaxTree, Item *symbolTable[], char *scope);
int searchEqual(Item *symbolTable[], TreeNode *syntaxTree, int index, char *scope);
void showSemanticError(SemanticError error, char *name, int line);

#endif