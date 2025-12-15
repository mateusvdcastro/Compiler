#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_simbolos.h"
#include "semantica.h"
#include "globals.h"
#include <unistd.h>

int semanticError = 0;


FunctionContext currentFunc = {"global", Type_void, 0, 0, 0};

// Conta parâmetros de uma função a partir do nó de parâmetros
int countFunctionParams(TreeNode *paramNode) {
    if (!paramNode || paramNode->stmtKind == ParamVoid) {
        return 0;
    }
    
    int count = 0;
    TreeNode *aux = paramNode;
    while (aux) {
        count++;
        aux = aux->sibling;
    }
    return count;
}

// Conta argumentos em uma chamada de função a partir do nó de expressão
int countFunctionArgs(TreeNode *argNode) {
    if (!argNode) {
        return 0;
    }
    
    int count = 0;
    TreeNode *aux = argNode;
    while (aux) {
        count++;
        aux = aux->sibling;
    }
    return count;
}

// Inserção na tabela dos statements (SEGUNDA PASSAGEM)
// Insere variáveis locais, processa returns
void analyzeStmt(TreeNode *tree, Item *table[], char *scope) {
    TreeNode *aux;

    if (!tree) return;

    // Declaração de função - apenas atualizar contexto
    if (tree->stmtKind == FunDeclK) {
        // Guardar contexto da função para análise de returns
        strcpy(currentFunc.funcName, tree->child[1]->lexeme);
        
        typeType type = (strcmp(tree->lexeme, "INT") == 0) ? Type_int : Type_void;
        currentFunc.returnType = type;
        currentFunc.paramCount = countFunctionParams(tree->child[0]);
        currentFunc.hasReturn = 0;
        currentFunc.hasReturnValue = 0;
    }

    // Declaração de variável local ou vetor local
    else if (tree->stmtKind == VarDeclK || tree->stmtKind == VetDeclK) {
        // Não é escopo "global" — é uma declaração local dentro de uma função
        if (strcmp(scope, "global") != 0) {
            if (strcmp(tree->lexeme, "INT") == 0) {
                // Verificar duplicata NO ESCOPO LOCAL ATUAL
                Item *existing = searchtable(table, tree->child[0]->lexeme, scope, tree->stmtKind);
                if (existing) {
                    showSemanticError(ErrVarRedecl, tree->child[0]->lexeme, tree->lineNum);
                } else {
                    insertable(table, tree->stmtKind, Type_int,
                               tree->child[0]->lexeme, scope, tree->lineNum);
                }
            } else {
                // void não pode ser usado em declaração de variável
                showSemanticError(ErrVoidVarDecl, tree->child[0]->lexeme, tree->lineNum);
            }
        }
    }

    // Declaração de retorno
    else if (tree->stmtKind == ReturnInK || tree->stmtKind == ReturnVoidK) {
        currentFunc.hasReturn = 1;
        if (tree->stmtKind == ReturnInK) {
            currentFunc.hasReturnValue = 1;
        }
        
        // ReturnInK = return expressão;
        // ReturnVoidK = return;
        
        if (tree->stmtKind == ReturnInK && currentFunc.returnType == Type_void) {
            // Função void não deve retornar valor
            showSemanticError(ErrReturnValueInVoid,
                              currentFunc.funcName, tree->lineNum);
        } else if (tree->stmtKind == ReturnVoidK && 
                   currentFunc.returnType == Type_int) {
            // Função int deve retornar valor
            showSemanticError(ErrReturnVoidInNonVoid,
                              currentFunc.funcName, tree->lineNum);
        }
    }
}

// Análise de expressões
void analyzeExp(TreeNode *tree, Item *table[], char *scope) {
    Item *item;
    Item *funcItem;

    if (!tree) return;

    // Uso de variável simples
    if (tree->expKind == IdK) {
        item = searchtableExp(table, tree->lexeme, scope, IdK);

        if (!item) {
            // Variável não encontrada em nenhum escopo
            // Verificar se é tentativa de usar função como variável
            funcItem = searchitemFunc(table, tree->lexeme);
            if (funcItem) {
                showSemanticError(ErrFuncCallMissingPar,
                                  tree->lexeme, tree->lineNum);
                addline(funcItem, tree->lineNum);
            } else {
                showSemanticError(ErrVarUndeclared,
                                  tree->lexeme, tree->lineNum);
            }
        } else if (item->Statement == FunDeclK) {
            // Item encontrado é uma função, não uma variável
            showSemanticError(ErrFuncCallMissingPar,
                              tree->lexeme, tree->lineNum);
            addline(item, tree->lineNum);
        } else {
            // É variável/parâmetro válido
            addline(item, tree->lineNum);
        }
    }

    // Chamada de função
    else if (tree->expKind == AtivK) {
        funcItem = searchtableExp(table, tree->lexeme, "global", AtivK);

        if (!funcItem) {
            showSemanticError(ErrFuncUndeclared,
                              tree->lexeme, tree->lineNum);
        } else {
            addline(funcItem, tree->lineNum);
            
            // Validar contagem de argumentos
            int argCount = countFunctionArgs(tree->child[0]);
            if (argCount != funcItem->paramCount) {
                showSemanticError(ErrWrongArgCount,
                                  tree->lexeme, tree->lineNum);
            }
            else {
                // Se temos informações de tipos de parâmetros, validar cada argumento
                if (funcItem->paramKinds != NULL) {
                    TreeNode *arg = tree->child[0];
                    int i = 0;
                    while (arg && i < funcItem->paramCount) {
                        int expected = funcItem->paramKinds[i];

                        // parâmetro de vetor: o argumento deve ser um único ID referenciando um vetor
                        if (expected == VetParamK) {
                            if (arg->expKind != IdK) {
                                showSemanticError(ErrArrayArgMismatch, tree->lexeme, tree->lineNum);
                            } else {
                                Item *aid = searchtableExp(table, arg->lexeme, scope, IdK);
                                if (!aid) {
                                    showSemanticError(ErrVarUndeclared, arg->lexeme, arg->lineNum);
                                } else if (!(aid->Statement == VetDeclK || aid->Statement == VetParamK)) {
                                    showSemanticError(ErrArrayArgMismatch, tree->lexeme, tree->lineNum);
                                }
                            }
                        }
                        // parâmetro inteiro: não aceitar passagem de vetor
                        else if (expected == VarParamK) {
                            if (arg->expKind == IdK) {
                                Item *aid = searchtableExp(table, arg->lexeme, scope, IdK);
                                if (aid && (aid->Statement == VetDeclK || aid->Statement == VetParamK)) {
                                    showSemanticError(ErrArrayArgMismatch, tree->lexeme, tree->lineNum);
                                }
                            }
                        }

                        arg = arg->sibling;
                        i++;
                    }
                }
            }
        }
    }

    // Atribuição
    else if (tree->expKind == AssignK) {
        // tree->child[0] = var (target)
        // tree->child[1] = expressão (rvalue)
        
        if (tree->child[1] && tree->child[1]->expKind == AtivK) {
            funcItem = searchtableExp(table, tree->child[1]->lexeme,
                                      "global", AtivK);
            if (funcItem && funcItem->DataType == Type_void) {
                showSemanticError(ErrAssignVoidFunc,
                                  tree->child[1]->lexeme, tree->lineNum);
            }
        }
    }

    // Uso de vetor indexado
    else if (tree->expKind == VetK) {
        item = searchtableExp(table, tree->lexeme, scope, VetK);

        if (!item) {
            showSemanticError(ErrVectorUndeclared,
                              tree->lexeme, tree->lineNum);
        } else {
            addline(item, tree->lineNum);
            
            // Verificar índice negativo (constante literal)
            if (tree->child[0] && tree->child[0]->expKind == ConstK) {
                int indexValue = atoi(tree->child[0]->lexeme);
                if (indexValue < 0) {
                    showSemanticError(ErrNegativeIndex,
                                      tree->lexeme, tree->lineNum);
                }
            }
        }
    }
}

// Insere declarações globais com validação de duplicatas
void insertGlobalDeclarations(TreeNode *tree, Item *table[]) {
    if (!tree) return;

    if (tree->nodeKind == StmtK && tree->stmtKind == FunDeclK) {
        typeType type = (strcmp(tree->lexeme, "INT") == 0) ? Type_int : Type_void;
        
        // Verificar duplicata
        Item *existing = searchtable(table, tree->child[1]->lexeme, "global", FunDeclK);
        if (existing) {
            showSemanticError(ErrFuncRedecl, tree->child[1]->lexeme, tree->lineNum);
        } else {
            // Contar parâmetros e inserir com paramCount
            int paramCount = countFunctionParams(tree->child[0]);
            insertableWithParams(table, FunDeclK, type,
                                tree->child[1]->lexeme, "global", tree->lineNum, paramCount);
        }
        
        // Inserir parâmetros da função
        if (tree->child[0] && tree->child[0]->stmtKind != ParamVoid) {
            TreeNode *param = tree->child[0];
            while (param) {
                // Parâmetros têm scope da função
                Item *paramExisting = searchtable(table, param->lexeme, 
                                                  tree->child[1]->lexeme, param->stmtKind);
                if (paramExisting) {
                    showSemanticError(ErrVarRedecl, param->lexeme, param->lineNum);
                } else {
                    insertable(table, param->stmtKind, Type_int, param->lexeme,
                              tree->child[1]->lexeme, param->lineNum);
                }
                param = param->sibling;
            }
            /* Após inserir parâmetros, armazenar os tipos dos parâmetros na entrada da função */
            Item *funcItem = searchtable(table, tree->child[1]->lexeme, "global", FunDeclK);
            if (funcItem && funcItem->paramCount > 0) {
                funcItem->paramKinds = (int*)calloc(funcItem->paramCount, sizeof(int));
                TreeNode *p = tree->child[0];
                int idx = 0;
                while (p && idx < funcItem->paramCount) {
                    funcItem->paramKinds[idx++] = p->stmtKind;
                    p = p->sibling;
                }
            }
        }
    } else if (tree->nodeKind == StmtK && 
               (tree->stmtKind == VarDeclK || tree->stmtKind == VetDeclK)) {
        if (strcmp(tree->lexeme, "INT") == 0) {
            // Verificar duplicata
            Item *existing = searchtable(table, tree->child[0]->lexeme, "global", tree->stmtKind);
            if (existing) {
                showSemanticError(ErrVarRedecl, tree->child[0]->lexeme, tree->lineNum);
            } else {
                insertable(table, tree->stmtKind, Type_int,
                           tree->child[0]->lexeme, "global", tree->lineNum);
            }
        } else {
            // void não pode ser usado em declaração de variável
            showSemanticError(ErrVoidVarDecl, tree->child[0]->lexeme, tree->lineNum);
        }
    }

    if (tree->sibling) {
        insertGlobalDeclarations(tree->sibling, table);
    }
}

// Segunda passagem: análise completa incluindo verificação de usos
void analyzeTreeSecondPass(TreeNode *tree, Item *table[], char *scope) {
    if (!tree) return;

    // Se for declaração de função, atualizar contexto
    if (tree->nodeKind == StmtK && tree->stmtKind == FunDeclK) {
        strcpy(currentFunc.funcName, tree->child[1]->lexeme);
        
        // Buscar a função na tabela para pegar tipo
        Item *funcItem = searchtableExp(table, tree->child[1]->lexeme, "global", AtivK);
        if (funcItem) {
            currentFunc.returnType = funcItem->DataType;
        }
        currentFunc.paramCount = countFunctionParams(tree->child[0]);
        currentFunc.hasReturn = 0;
    }

    // Processar statements (var decl, returns)
    if (tree->nodeKind == StmtK && 
        (tree->stmtKind == ReturnInK || tree->stmtKind == ReturnVoidK || 
         tree->stmtKind == VarDeclK || tree->stmtKind == VetDeclK ||
         tree->stmtKind == FunDeclK)) {
        analyzeStmt(tree, table, scope);
    }

    if (tree->nodeKind == ExpK) {
        analyzeExp(tree, table, scope);
    }

    // Recursão nos filhos
    for (int i = 0; i < 3; i++) {
        if (tree->child[i]) {
            // Se função, usar nome da função como scope local
            if (tree->stmtKind == FunDeclK && i == 2) {
                analyzeTreeSecondPass(tree->child[i], table, tree->child[1]->lexeme);
            } else {
                analyzeTreeSecondPass(tree->child[i], table, scope);
            }
        }
    }

    // Recursão nos irmãos
    if (tree->sibling) {
        analyzeTreeSecondPass(tree->sibling, table, scope);
    }
}

// Entrada principal de análise semântica
void analyzeTree(TreeNode *tree, Item *table[], char *scope) {
    // Inserir funções pré-definidas (input, output)
    // int input(void) - 0 parâmetros
    insertableWithParams(table, FunDeclK, Type_int, "input", "global", 0, 0);
    // void output(int x) - 1 parâmetro
    insertableWithParams(table, FunDeclK, Type_void, "output", "global", 0, 1);
    
    // Primeira passagem: coletar todas as declarações globais (sem duplicatas)
    insertGlobalDeclarations(tree, table);
    
    // Segunda passagem: análise completa com validação
    analyzeTreeSecondPass(tree, table, scope);
    
    // Verificação final (ex.: main deve ser void main(void))
    finalizeSemanticChecks(tree, table);
}

// Verificação de duplicatas (usada por ambas passagens)
int searchEqual(Item *table[], TreeNode *tree, int idx, char *scope) {
    Item *item = searchtable(table, tree->child[idx]->lexeme, scope, tree->stmtKind);

    if (!item) return 1;

    if (item->Statement == FunDeclK && tree->stmtKind == FunDeclK) {
        showSemanticError(ErrFuncRedecl,
                          tree->child[idx]->lexeme, tree->lineNum);
    } else if (item->Statement != FunDeclK && tree->stmtKind != FunDeclK) {
        if (strcmp(item->Scope, scope) != 0 &&
            strcmp(item->Scope, "global") != 0)
            return 1;

        showSemanticError(ErrVarRedecl,
                          tree->child[idx]->lexeme, tree->lineNum);
    } else if (item->Statement == FunDeclK) {
        showSemanticError(ErrFuncAsVar,
                          tree->child[idx]->lexeme, tree->lineNum);
    } else {
        showSemanticError(ErrVarAsFunc,
                          tree->child[idx]->lexeme, tree->lineNum);
    }

    return 0;
}

// Mensagens de erro
void showSemanticError(SemanticError err, char *name, int line) {
    semanticError++;

    int tty = isatty(STDOUT_FILENO);
    const char *start = tty ? "\x1b[1;31m" : "";
    const char *end = tty ? "\x1b[0m" : "";

    switch (err) {
        case ErrVoidVarDecl:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Variável '%s' declarada como void%s\n\n",
                   start, name, line, name, end);
            break;
        case ErrFuncRedecl:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Função '%s' já declarada%s\n\n",
                   start, name, line, name, end);
            break;
        case ErrVarRedecl:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Variável '%s' já declarada%s\n\n",
                   start, name, line, name, end);
            break;
        case ErrVarAsFunc:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Identificador '%s' já declarado como variável%s\n\n",
                   start, name, line, name, end);
            break;
        case ErrFuncAsVar:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Identificador '%s' já declarado como função%s\n\n",
                   start, name, line, name, end);
            break;
        case ErrVarUndeclared:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Variável '%s' não declarada%s\n\n",
                   start, name, line, name, end);
            break;
        case ErrFuncUndeclared:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Função '%s' não declarada%s\n\n",
                   start, name, line, name, end);
            break;
        case ErrAssignVoidFunc:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Atribuição inválida: função '%s' do tipo void%s\n\n",
                   start, name, line, name, end);
            break;
        case ErrMainMissing:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Função 'main' não declarada%s\n\n",
                   start, name ? name : "main", line, end);
            break;
        case ErrVectorUndeclared:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Vetor '%s' não declarado%s\n\n",
                   start, name, line, name, end);
            break;
        case ErrFuncCallMissingPar:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Chamada inválida de função '%s'%s\n\n",
                   start, name, line, name, end);
            break;
        case ErrReturnValueInVoid:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Função '%s' declarada void não pode retornar valor%s\n\n",
                   start, name, line, name, end);
            break;
        case ErrReturnVoidInNonVoid:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Função '%s' deve retornar valor%s\n\n",
                   start, name, line, name, end);
            break;
        case ErrWrongArgCount:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Número errado de argumentos na chamada a '%s'%s\n\n",
                   start, name, line, name, end);
            break;
        case ErrArrayArgMismatch:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Argumento de vetor inválido para parâmetro de vetor '%s'%s\n\n",
                   start, name, line, name, end);
            break;
        case ErrNegativeIndex:
            printf("%sERRO SEMANTICO: %s LINHA: %d: Índice negativo em matriz%s\n\n",
                   start, name ? name : "", line, end);
            break;
        default:
            printf("%sERRO SEMANTICO: %s LINHA: %d%s\n\n", start, name ? name : "", line, end);
            break;
    }
}

// Verificações finais após análise completa
void finalizeSemanticChecks(TreeNode *tree, Item *table[]) {
    // Verificar se main existe e tem assinatura correta
    Item *mainFunc = searchtableExp(table, "main", "global", AtivK);
    
    if (!mainFunc) {
        printf("\033[1;31mERRO SEMANTICO, LINHA: 0\033[0m");
        printf(": Função 'main' não declarada\n\n");
        semanticError++;
    } else if (mainFunc->DataType != Type_void) {
        printf("\033[1;31mERRO SEMANTICO (MAIN)\033[0m");
        printf(": Função 'main' deve retornar void\n\n");
        semanticError++;
    } else {
        // Verificar se main é a última declaração
        TreeNode *curr = tree;
        int foundMain = 0;
        
        // Encontrar main na árvore e verificar se há irmãos após
        while (curr) {
            if (curr->nodeKind == StmtK && curr->stmtKind == FunDeclK) {
                if (curr->child[1] && strcmp(curr->child[1]->lexeme, "main") == 0) {
                    foundMain = 1;
                    // Se main tem irmãos (next sibling), há declaração após main
                    if (curr->sibling) {
                        printf("\033[1;31mERRO SEMANTICO, LINHA: %d\033[0m", curr->sibling->lineNum);
                        printf(": Declaração após função 'main'\n\n");
                        semanticError++;
                    }
                    break;
                }
            }
            curr = curr->sibling;
        }
    }
    
    // Verificar todas as funções int para garantir que têm return com valor
    verifyIntFunctionsReturn(tree);
}

// Verifica recursivamente se funções int tem return com valor
void verifyIntFunctionsReturn(TreeNode *tree) {
    if (!tree) return;
    
    if (tree->nodeKind == StmtK && tree->stmtKind == FunDeclK) {
        // Só verificar funções int (não void)
        if (strcmp(tree->lexeme, "INT") == 0) {
            // Rastrear contexto da função
            strcpy(currentFunc.funcName, tree->child[1]->lexeme);
            currentFunc.returnType = Type_int;
            currentFunc.hasReturnValue = 0;
            
            // Traversar o corpo da função para encontrar returns
            int anyReturn = 0;
            if (tree->child[2]) {
                anyReturn = checkForAnyReturn(tree->child[2]);
                checkForReturnValue(tree->child[2]);
            }

            // Se não há nenhum return na função int, erro
            if (!anyReturn) {
                printf("\033[1;31mERRO SEMANTICO, LINHA: %d\033[0m", tree->lineNum);
                printf(": Função '%s' deve retornar valor\n\n", tree->child[1]->lexeme);
                semanticError++;
            }
        }
    }
    
    // Recursão nos irmãos
    if (tree->sibling) {
        verifyIntFunctionsReturn(tree->sibling);
    }
}

// Busca por ReturnInK no corpo da função
void checkForReturnValue(TreeNode *tree) {
    if (!tree) return;
    
    if (tree->stmtKind == ReturnInK) {
        currentFunc.hasReturnValue = 1;
        return;
    }
    
    // Busca nos filhos
    for (int i = 0; i < 3; i++) {
        if (tree->child[i] && currentFunc.hasReturnValue == 0) {
            checkForReturnValue(tree->child[i]);
        }
    }
    
    // Busca nos irmãos
    if (tree->sibling && currentFunc.hasReturnValue == 0) {
        checkForReturnValue(tree->sibling);
    }
}

// Retorna 1 se encontrar qualquer return (com ou sem valor) no nó
int checkForAnyReturn(TreeNode *tree) {
    if (!tree) return 0;

    if (tree->nodeKind == StmtK && (tree->stmtKind == ReturnInK || tree->stmtKind == ReturnVoidK)) {
        return 1;
    }

    // Verifica filhos
    for (int i = 0; i < 3; i++) {
        if (tree->child[i]) {
            if (checkForAnyReturn(tree->child[i])) return 1;
        }
    }

    // Verifica irmãos
    if (tree->sibling) {
        if (checkForAnyReturn(tree->sibling)) return 1;
    }

    return 0;
}
