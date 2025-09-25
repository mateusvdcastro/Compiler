#include "globals.h"
#include "syntax_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a new tree node
NODEPOINTER createNode(char lexeme[MAXLEXEME], int lineNum, NodeKind nodeKind, StmtKind stmtKind, ExpKind expKind) {
    NODEPOINTER newnode = (NODEPOINTER) malloc(sizeof(TreeNode));
    if (newnode == NULL) {
        printf("Error: out of memory\n");
        exit(1);
    }
    
    // Initialize all fields
    for (int i = 0; i < 3; i++) {
        newnode->child[i] = NULL;
    }
    newnode->sibling = NULL;
    newnode->nodeKind = nodeKind;
    newnode->stmtKind = stmtKind;
    newnode->expKind = expKind;
    newnode->lineNum = lineNum;
    
    // Copy lexeme safely
    strncpy(newnode->lexeme, lexeme, MAXLEXEME - 1);
    newnode->lexeme[MAXLEXEME - 1] = '\0';
    
    return newnode;
}

// Function to create a new tree node with default values
NODEPOINTER newNode() {
    NODEPOINTER newnode = (NODEPOINTER) malloc(sizeof(TreeNode));

    if (newnode == NULL) {
        printf("Error: out of memory\n");
        exit(1);
    }
    
    // Initialize all fields to default values
    for (int i = 0; i < 3; i++) {
        newnode->child[i] = NULL;
    }

    newnode->sibling = NULL;
    newnode->nodeKind = NullK;
    newnode->stmtKind = NullDecl;
    newnode->expKind = NullExpK;
    newnode->lineNum = 0;
    memset(newnode->lexeme, 0, MAXLEXEME);
    
    return newnode;
}

// Function to add a sibling to a node
NODEPOINTER addSibling(NODEPOINTER root, NODEPOINTER node) {
    if (root == NULL) {
        return node;
    }
    if (node == NULL) {
        return root;
    }
    
    NODEPOINTER temp = root;
    while (temp->sibling != NULL) {
        temp = temp->sibling;
    }
    temp->sibling = node;
    
    return root;
}

// Function to add a child to a node
NODEPOINTER addChild(NODEPOINTER root, NODEPOINTER node) {
    if (root == NULL || node == NULL) {
        return root;
    }
    
    // Find the first available child slot
    for (int i = 0; i < 3; i++) {
        if (root->child[i] == NULL) {
            root->child[i] = node;
            return root;
        }
    }
    
    // // If all child slots are taken, add as sibling to the last child
    // if (root->child[2] != NULL) {
    //     root->child[2] = addSibling(root->child[2], node);
    // }
    
    return root;
}

//Mostra a árvore
int flagMA = 0; //Flag para mostrar o primeiro print apenas uma vez.
void mostraArvore(NODEPOINTER root, int num){
    if(flagMA == 0){
        flagMA = 1;
        fprintf(fileOUTPUT, "\n========== Arvore de Analise Sintatica ========== \n");
    }
    
    if(root == NULL){
        return;
    }

    for(int i = 0; i < num; i++){
        fprintf(fileOUTPUT, "\t");
    }
    fprintf(fileOUTPUT, "%s\n", root->lexeme);
    
    for(int i = 0; i < 3; i++){
        mostraArvore(root->child[i], num + 1);
    }
    mostraArvore(root->sibling, num);
    
}

// Function to display the syntax tree
void showTree(NODEPOINTER root, int num) {
    if (root == NULL) {
        return;
    }
    
    // Print indentation
    for (int i = 0; i < num; i++) {
        printf("  ");
    }
    
    // Print node information
    printf("%s", root->lexeme);
    if (strlen(root->lexeme) > 0) {
        printf(" ");
    }
    
    // Print node type information
    if (root->nodeKind == StmtK) {
        printf("(Stmt: ");
        switch (root->stmtKind) {
            case IfK: printf("If"); break;
            case WhileK: printf("While"); break;
            case ReturnInK: printf("ReturnInt"); break;
            case ReturnVoidK: printf("ReturnVoid"); break;
            case CallK: printf("Call"); break;
            case VarDeclK: printf("VarDecl"); break;
            case VetDeclK: printf("ArrayDecl"); break;
            case FunDeclK: printf("FunDecl"); break;
            case CompK: printf("Compound"); break;
            case VarParamK: printf("VarParam"); break;
            case VetParamK: printf("ArrayParam"); break;
            case ParamVoid: printf("VoidParam"); break;
            default: printf("Unknown"); break;
        }
        printf(")");
    } else if (root->nodeKind == ExpK) {
        printf("(Exp: ");
        switch (root->expKind) {
            case OpK: printf("Op"); break;
            case OpRel: printf("RelOp"); break;
            case ConstK: printf("Const"); break;
            case IdK: printf("Id"); break;
            case AtivK: printf("Call"); break;
            case VetK: printf("Array"); break;
            case AssignK: printf("Assign"); break;
            case TypeK: printf("Type"); break;
            default: printf("Unknown"); break;
        }
        printf(")");
    }
    
    printf("\n");
    
    // Recursively print children
    for (int i = 0; i < 3; i++) {
        if (root->child[i] != NULL) {
            showTree(root->child[i], num + 1);
        }
    }
    
    // Print siblings at the same level
    if (root->sibling != NULL) {
        showTree(root->sibling, num);
    }
}

// Function to free the syntax tree
void freeTree(NODEPOINTER root) {
    if (root == NULL) {
        return;
    }
    
    // Free all children
    for (int i = 0; i < 3; i++) {
        if (root->child[i] != NULL) {
            freeTree(root->child[i]);
        }
    }
    
    // Free siblings
    if (root->sibling != NULL) {
        freeTree(root->sibling);
    }
    
    // Free the current node
    free(root);
}