#ifndef _SYNTAX_TREE_H_
#define _SYNTAX_TREE_H_ 1

// Types of nodes that can exist in the tree
typedef enum { StmtK, ExpK, NullK } NodeKind; // Stmt = Statement and Exp = Expression

typedef enum { Type_int, Type_void } typeType; // Data types

// Subtypes for statement nodes
typedef enum { 
    IfK, // If statement
    WhileK, // While statement
    ReturnInK, // Return of integer function
    ReturnVoidK, // Return of void function
    CallK, // Function call statement
    NullDecl, // Null declaration
    VarDeclK, // Variable declaration
    VetDeclK, // Array declaration
    FunDeclK, // Function declaration
    CompK, // Compound statement
    VarParamK, // Variable parameter declaration.
    VetParamK, // Array parameter declaration.
    ParamVoid // Function declaration with void parameter.
} StmtKind;

// Subtypes for expression nodes
typedef enum { 
    OpK, // Operator
    OpRel, // Relational operator
    ConstK, // Constant numeric value
    IdK, // Identifier
    AtivK, // Function call
    VetK, // Array
    AssignK, // Assignment
    TypeK, // Type
    NullExpK // Null expression
} ExpKind;

/* Declarations for the syntax tree */

typedef struct TreeNode {
    int lineNum;
    NodeKind nodeKind;
    StmtKind stmtKind;
    ExpKind expKind;
    char lexeme[MAXLEXEME];
    struct TreeNode *child[3]; // Up to 3 children
    struct TreeNode *sibling; // Pointer to the next sibling
} TreeNode;

typedef TreeNode *NODEPOINTER;

// Function to create a new tree node
NODEPOINTER createNode(char lexeme[MAXLEXEME], int lineNum, NodeKind nodeKind, StmtKind stmtKind, ExpKind expKind);

// Functions to add siblings and children
NODEPOINTER addSibling(NODEPOINTER root, NODEPOINTER node);
NODEPOINTER addChild(NODEPOINTER root, NODEPOINTER node);

// Function to create a new tree node with default values
NODEPOINTER newNode();

// Function to display the syntax tree
void showTree(NODEPOINTER root, int num);
void mostraArvore(NODEPOINTER root, int num);

void freeTree(NODEPOINTER root);

#endif