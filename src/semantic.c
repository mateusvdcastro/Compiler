#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_simbolos.h"
#include "semantica.h"
#include "globals.h"

int semanticError = 0;

/* =====================================================
   INSERÇÃO DE DECLARAÇÕES NA TABELA DE SÍMBOLOS
   ===================================================== */

void analyzeStmt(TreeNode *tree, Item *table[], char *scope) {
    TreeNode *aux;
    typeType type;

    /* ---------- Declaração de função ---------- */
    if (tree->stmtKind == FunDeclK) {

        type = (strcmp(tree->lexeme, "INT") == 0) ? Type_int : Type_void;
        strcpy(scope, tree->child[1]->lexeme);

        if (searchEqual(table, tree, 1, scope))
            insertable(table, FunDeclK, type,
                       tree->child[1]->lexeme, "global", tree->lineNum);

        /* ---------- Parâmetros ---------- */
       if (tree->child[0] && tree->child[0]->stmtKind != ParamVoid) {
            aux = tree->child[0];
            while (aux) {
                if (searchEqual(table, aux, 0, scope)) {
                    insertable(table, aux->stmtKind, Type_int, aux->lexeme, scope, aux->lineNum);
                }
                aux = aux->sibling;
            }
        }

    }

    /* ---------- Variável ou vetor ---------- */
    else if (tree->stmtKind == VarDeclK || tree->stmtKind == VetDeclK) {
        if (searchEqual(table, tree, 0, scope)) {
            if (strcmp(tree->lexeme, "INT") == 0) {
                insertable(table,
                           tree->stmtKind,
                           Type_int,
                           tree->child[0]->lexeme,
                           scope,
                           tree->lineNum);
            } else {
                showSemanticError(ErrVoidVarDecl,
                                  tree->child[0]->lexeme,
                                  tree->lineNum);
            }
        }
    }
}

/* =====================================================
   ANÁLISE DE EXPRESSÕES
   ===================================================== */

void analyzeExp(TreeNode *tree, Item *table[], char *scope) {
    Item *item;

    /* ---------- Uso de variável ---------- */
    if (tree->expKind == IdK) {
        item = searchtableExp(table, tree->lexeme, scope, IdK);

        if (!item) {
            if (searchtableExp(table, tree->lexeme, "global", AtivK))
                showSemanticError(ErrFuncCallMissingPar,
                                  tree->lexeme, tree->lineNum);
            else
                showSemanticError(ErrVarUndeclared,
                                  tree->lexeme, tree->lineNum);
        } else {
            addline(item, tree->lineNum);
        }
    }

    /* ---------- Chamada de função ---------- */
    else if (tree->expKind == AtivK) {
        item = searchtableExp(table, tree->lexeme, "global", AtivK);

        if (!item)
            showSemanticError(ErrFuncUndeclared,
                              tree->lexeme, tree->lineNum);
        else
            addline(item, tree->lineNum);
    }

    /* ---------- Atribuição ---------- */
    else if (tree->expKind == AssignK) {
        if (tree->child[1]->expKind == AtivK) {
            item = searchtableExp(table,
                                  tree->child[1]->lexeme,
                                  "global",
                                  AtivK);
            if (item && item->DataType == Type_void)
                showSemanticError(ErrAssignVoidFunc,
                                  tree->child[1]->lexeme,
                                  tree->lineNum);
        }
    }

    /* ---------- Uso de vetor ---------- */
    else if (tree->expKind == VetK) {
        item = searchtableExp(table, tree->lexeme, scope, VetK);

        if (!item)
            showSemanticError(ErrVectorUndeclared,
                              tree->lexeme, tree->lineNum);
        else
            addline(item, tree->lineNum);
    }
}

/* =====================================================
   PERCORRIMENTO DA ÁRVORE
   ===================================================== */

void analyzeTree(TreeNode *tree, Item *table[], char *scope) {
    char localScope[MAXLEXEME];
    strcpy(localScope, scope);

    if (!tree) return;

    if (tree->nodeKind == StmtK)
        analyzeStmt(tree, table, localScope);

    if (tree->nodeKind == ExpK)
        analyzeExp(tree, table, localScope);

    if (tree->expKind != AtivK) {
        for (int i = 0; i < 3; i++)
            analyzeTree(tree->child[i], table, localScope);
    }

    analyzeTree(tree->sibling, table,
                strcmp(scope, "global") == 0 ? scope : localScope);
}

/* =====================================================
   VERIFICAÇÃO DE DECLARAÇÕES DUPLICADAS
   ===================================================== */

int searchEqual(Item *table[], TreeNode *tree, int idx, char *scope) {
    Item *item =
        searchtable(table, tree->child[idx]->lexeme, scope, tree->stmtKind);

    if (!item) return 1;

    if (item->Statement == FunDeclK && tree->stmtKind == FunDeclK)
        showSemanticError(ErrFuncRedecl,
                          tree->child[idx]->lexeme,
                          tree->lineNum);

    else if (item->Statement != FunDeclK && tree->stmtKind != FunDeclK) {
        if (strcmp(item->Scope, scope) != 0 &&
            strcmp(item->Scope, "global") != 0)
            return 1;

        showSemanticError(ErrVarRedecl,
                          tree->child[idx]->lexeme,
                          tree->lineNum);
    }

    else if (item->Statement == FunDeclK)
        showSemanticError(ErrFuncAsVar,
                          tree->child[idx]->lexeme,
                          tree->lineNum);
    else
        showSemanticError(ErrVarAsFunc,
                          tree->child[idx]->lexeme,
                          tree->lineNum);

    return 0;
}

/* =====================================================
   MENSAGENS DE ERRO
   ===================================================== */

void showSemanticError(SemanticError err, char *name, int line) {
    semanticError++;

    printf("\033[1;31mERRO SEMANTICO, LINHA: %d\033[0m", line);

    switch (err) {
        case ErrVoidVarDecl:
            printf(": Variável '%s' declarada como void\n\n", name); break;
        case ErrFuncRedecl:
            printf(": Função '%s' já declarada\n\n", name); break;
        case ErrVarRedecl:
            printf(": Variável '%s' já declarada\n\n", name); break;
        case ErrVarAsFunc:
            printf(": Identificador '%s' já declarado como variável\n\n", name); break;
        case ErrFuncAsVar:
            printf(": Identificador '%s' já declarado como função\n\n", name); break;
        case ErrVarUndeclared:
            printf(": Variável '%s' não declarada\n\n", name); break;
        case ErrFuncUndeclared:
            printf(": Função '%s' não declarada\n\n", name); break;
        case ErrAssignVoidFunc:
            printf(": Atribuição inválida: função '%s' do tipo void\n\n", name); break;
        case ErrVectorUndeclared:
            printf(": Vetor '%s' não declarado\n\n", name); break;
        case ErrFuncCallMissingPar:
            printf(": Chamada inválida de função '%s'\n\n", name); break;
    }
}
