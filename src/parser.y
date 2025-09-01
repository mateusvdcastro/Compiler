%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "syntax_tree.h"

#define YYSTYPE NODEPOINTER
#define MAX_NODES 10000

static int yylex(void);
void yyerror(char *s);
int yyparse(void);

enum yytokentype auxError;

int syntax_errors = 0;

NODEPOINTER syntax_tree = NULL;

void showTree(NODEPOINTER root, int num);
enum yytokentype getToken(void);
NODEPOINTER parse(void);

char auxLexeme[MAXLEXEME];
NODEPOINTER nodes[MAX_NODES];
int nodeCount = 0;

// Safe stack access function
char* getStackTop() {
    if (indStack >= 0 && indStack < 4) {
        char* result = stack[indStack];
        indStack--;
        return result;
    }
    return "";
}

%}

%token NUM SOMA SUB MULT DIV INT
%token ID VOID WHILE ELSE IF ABREPARENTESES FECHAPARENTESES
%token RETURN COMMA ABRECHAVES FECHACHAVES SEMICOLON
%token ATRIB ABRECOLCHETES FECHACOLCHETES
%token EQ NEQ LT LET GT GET ERRO

%%

programa			: declaracao_lista {
                        syntax_tree = $1;
                    }

                    ;
            
declaracao_lista	: declaracao_lista declaracao {  
                        if($1 != NULL){
                            $$ = $1;
                            addSibling($$, $2);
                        }
                        else{
                            $$ = $2;
                        }
                      }
                    | declaracao {$$ = $1;}
                    ;

declaracao			: var_declaracao {$$ = $1;}
                    | fun_declaracao {$$ = $1;}				
                    ;

var_declaracao		: tipo_especificador ID SEMICOLON {
                        $$ = $1;
                        $$->nodeKind = StmtK;
                        $$->stmtKind = VarDeclK;
                        $$->lineNum = lineNum;
                    
                        NODEPOINTER aux = newNode();

                        strcpy(aux->lexeme, stack[indStack]);
                        indStack--;

                        //strcpy(aux->lexeme, id);
                        addChild($$, aux);

                        nodes[nodeCount] = aux;
                        nodeCount++;

                        }
                    | tipo_especificador error SEMICOLON    {
                        yyerrok;
                        printf(ANSI_COLOR_GREEN "RECUPERAÇÃO DE ERRO: " ANSI_COLOR_RESET "Ignorando declaração inválida\n");
                        $$ = NULL;
                    }
                    | tipo_especificador ID ABRECOLCHETES NUM FECHACOLCHETES SEMICOLON {
                        $$ = $1;
                        $$->nodeKind = StmtK;
                        $$->stmtKind = VetDeclK;
                        $$->lineNum = lineNum;

                        NODEPOINTER aux = newNode();
                        NODEPOINTER aux2 = newNode();
                        
                        strcpy(aux->lexeme, stack[indStack]);
                        indStack--;

                        nodes[nodeCount] = aux;
                        nodeCount++;

                        strcpy(aux2->lexeme, stack[indStack]);
                        indStack--;
                        
                        addChild($$, aux2);
                        addChild($$, aux);

                        nodes[nodeCount] = aux2;
                        nodeCount++;
                    }
                    | tipo_especificador error FECHACOLCHETES SEMICOLON {
                        yyerrok;
                        printf(ANSI_COLOR_GREEN "RECUPERAÇÃO DE ERRO: " ANSI_COLOR_RESET "Ignorando declaração inválida\n");
                        $$ = NULL;
                    }
                    ;

tipo_especificador 	: INT {
                        $$ = newNode();
                        strcpy($$->lexeme, "INT");
                        $$->lineNum = lineNum;

                        nodes[nodeCount] = $$;
                        nodeCount++;
                    }
                    | VOID {
                        $$ = newNode();
                        strcpy($$->lexeme, "VOID");
                        $$->lineNum = lineNum;

                        nodes[nodeCount] = $$;
                        nodeCount++;
                    }
                    ;
                    
                    /* Trocar o ID da funcao por um IDFUNC */
fun_declaracao		: tipo_especificador fun_id ABREPARENTESES params FECHAPARENTESES composto_decl { 
                        //strcpy(auxLexema, "")
                        $$ = $1;

                        addChild($$, $4);
                        addChild($$, $2);
                        addChild($2, $6);
                        
                        $$->nodeKind = StmtK;
                        $$->stmtKind = FunDeclK;
                    }
                    ;

fun_id				: ID {
                        $$ = newNode();
                        
                        strcpy($$->lexeme, stack[indStack]);
                        indStack--;

                        //strcpy($$->lexeme, auxNome);
                        $$->lineNum = lineNum;

                        nodes[nodeCount] = $$;
                        nodeCount++;
                    }
                    ;	

params				: param_lista {$$ = $1;}
                    | VOID {
                        $$ = newNode();
                        $$->nodeKind = StmtK;
                        $$->lineNum = lineNum;
                        $$->stmtKind = ParamVoid;
                        strcpy($$->lexeme, "VOID");

                        nodes[nodeCount] = $$;
                        nodeCount++;
                    }
                    ;

param_lista			: param_lista COMMA param {
                        if($1 != NULL){
                            $$ = $1;
                            addSibling($$, $3);
                        }
                        else{
                            $$ = $3;
                        }						
                    }
                    | param {$$ = $1;}
                    ;

param				: tipo_especificador ID {
                        $$ = $1;
                        $$->nodeKind = StmtK;
                        $$->lineNum = lineNum;
                        $$->stmtKind = VarParamK;

                        NODEPOINTER aux = newNode();

                        strcpy(aux->lexeme, stack[indStack]);
                        indStack--;
                    
                        //strcpy(aux->lexeme, id);
                        addChild($$, aux);

                        nodes[nodeCount] = aux;
                        nodeCount++;

                    }
                    | tipo_especificador ID ABRECOLCHETES FECHACOLCHETES {
                        $$ = $1;
                        $$->nodeKind = StmtK;
                        $$->lineNum = lineNum;
                        $$->stmtKind = VetParamK;
                        NODEPOINTER aux = newNode();

    
                        strcpy(aux->lexeme, stack[indStack]);
                        indStack--;

                        //strcpy(aux->lexeme, id);
                        addChild($$, aux);		

                        nodes[nodeCount] = aux;
                        nodeCount++;	
                    }
                    ;

composto_decl		: ABRECHAVES local_declaracoes statement_lista FECHACHAVES { 
                        if($2 != NULL){
                            $$ = $2;
                            addSibling($$, $3);
                        }
                        else{
                            $$ = $3;
                        }
                    }
                    ;

local_declaracoes 	: local_declaracoes var_declaracao {
                        if($1 != NULL){
                            $$ = $1;
                            addSibling($$, $2);
                        }
                        else{
                            $$ = $2;
                        }

                    }
                    | %empty {$$ = NULL;}
                    ;

statement_lista 	: statement_lista statement {
                        if($1 != NULL){
                            $$ = $1;
                            addSibling($$, $2);
                        }
                        else{
                            $$ = $2;
                        }
                    }
                    | %empty {$$ = NULL;}
                    ;
            
statement			: expressao_decl {$$ = $1;}
                    | composto_decl {$$ = $1;}
                    | selecao_decl {$$ = $1;}
                    | iteracao_decl {$$ = $1;}
                    | retorno_decl {$$ = $1;}
                    ;

expressao_decl		: expressao SEMICOLON {$$ = $1;}
                    | SEMICOLON {$$ = NULL;}
                    | error SEMICOLON {
                        yyerrok;
                        printf(ANSI_COLOR_GREEN "RECUPERAÇÃO DE ERRO: " ANSI_COLOR_RESET "Sincronizando em ';'\n");
                        $$ = NULL;
                    }
                    ;
            
selecao_decl		: IF ABREPARENTESES expressao FECHAPARENTESES statement %prec IFX {
                        $$ = newNode();
                        strcpy($$->lexeme, "IF");
                        $$->nodeKind = StmtK;
                        $$->lineNum = lineNum;
                        $$->stmtKind = IfK;

                        addChild($$, $3);
                        addChild($$, $5);		

                        nodes[nodeCount] = $$;
                        nodeCount++;
                    }
                    | IF ABREPARENTESES expressao FECHAPARENTESES statement ELSE statement {
                        $$ = newNode();
                        strcpy($$->lexeme, "IF");
                        $$->nodeKind = StmtK;
                        $$->lineNum = lineNum;
                        $$->stmtKind = IfK;

                        addChild($$, $3);
                        addChild($$, $5);		
                        addChild($$, $7);

                        nodes[nodeCount] = $$;
                        nodeCount++;
                    }
                    ;
            
iteracao_decl		: WHILE ABREPARENTESES expressao FECHAPARENTESES statement {
                        $$ = newNode();
                        strcpy($$->lexeme, "WHILE");
                        $$->nodeKind = StmtK;
                        $$->lineNum = lineNum;
                        $$->stmtKind = WhileK;

                        addChild($$, $3);
                        addChild($$, $5);

                        nodes[nodeCount] = $$;
                        nodeCount++;

                    }
                    ;
            
retorno_decl		: RETURN SEMICOLON { 
                        $$ = newNode();
                        $$->nodeKind = StmtK;
                        $$->lineNum = lineNum;
                        $$->stmtKind = ReturnVoidK;
                        strcpy($$->lexeme, "ReturnVOID");

                        nodes[nodeCount] = $$;
                        nodeCount++;
                        
                    }
                    | RETURN expressao SEMICOLON {
                        $$ = newNode();
                        $$->nodeKind = StmtK;
                        $$->lineNum = lineNum;
                        $$->stmtKind = ReturnInK;
                        strcpy($$->lexeme, "ReturnINT");

                        addChild($$, $2);

                        nodes[nodeCount] = $$;
                        nodeCount++;
                    }
                    ;

expressao			: var ATRIB expressao {
                        $$ = newNode();
                        strcpy($$->lexeme, "=");
                        $$->nodeKind = ExpK;
                        $$->lineNum = lineNum;
                        $$->expKind = AssignK;

                        addChild($$, $1);
                        addChild($$, $3);

                        nodes[nodeCount] = $$;
                        nodeCount++;

                    }
                    | simples_expressao {$$ = $1;}
                    ;

var 				: ID {
                        $$ = newNode();
                        $$->nodeKind = ExpK;
                        $$->lineNum = lineNum;
                        $$->expKind = IdK;
                        

                        strcpy($$->lexeme, stack[indStack]);
                        /*
                        FILE * arquivoAux = fopen("arquivoAux.txt", "a+");
                        fprintf(arquivoAux, "%s\n", $$->lexeme);
                        fclose(arquivoAux);
                        */
                        indStack--;
                        //strcpy($$->lexema, id);

                        nodes[nodeCount] = $$;
                        nodeCount++;

                    }
                    | ID ABRECOLCHETES expressao FECHACOLCHETES{
                        $$ = newNode();

                        $$->nodeKind = ExpK;
                        $$->lineNum = lineNum;
                        $$->expKind = VetK;
                        
                        //strcpy($$->lexema, id);
                        strcpy($$->lexeme, stack[indStack]);
                        indStack--;

                        addChild($$, $3);

                        nodes[nodeCount] = $$;
                        nodeCount++;
                        
                    }
                    ;
            
simples_expressao	: soma_expressao relacional soma_expressao {
                        $$ = $2;
                        $$->nodeKind = ExpK;
                        $$->lineNum = lineNum;
                        $$->expKind = OpRel;

                        addChild($$, $1);
                        addChild($$, $3);	
                        
                    }
                    | soma_expressao {$$ = $1;}
                    ;
        
relacional			: operador_relacional {
                        $$ = $1;
                    }
                    ;

operador_relacional	: EQ {
                        $$ = newNode();
                        strcpy($$->lexeme, "==");

                        nodes[nodeCount] = $$;
                        nodeCount++;
                        
                    }

                    | NEQ {
                        $$ = newNode();
                        strcpy($$->lexeme, "!=");

                        nodes[nodeCount] = $$;
                        nodeCount++;
                        
                    }

                    | LT {
                        $$ = newNode();
                        strcpy($$->lexeme, "<");

                        nodes[nodeCount] = $$;
                        nodeCount++;
                        
                    }
                    
                    | GT {
                        $$ = newNode();
                        strcpy($$->lexeme, ">");

                        nodes[nodeCount] = $$;
                        nodeCount++;
                        
                    }
                    
                    | LET {
                        $$ = newNode();
                        strcpy($$->lexeme, "<=");

                        nodes[nodeCount] = $$;
                        nodeCount++;
                        
                    }

                    | GET {
                        $$ = newNode();
                        strcpy($$->lexeme, ">=");

                        nodes[nodeCount] = $$;
                        nodeCount++;
                    }
                    ;


soma_expressao		: soma_expressao soma termo {
                        $$ = $2;
                        $$->nodeKind = ExpK;
                        $$->lineNum = lineNum;
                        $$->expKind = OpK;

                        addChild($$, $1);
                        addChild($$, $3);
                    }
                    | termo {$$ = $1;}
                    ;
            
soma				: SOMA {
                        $$ = newNode();
                        strcpy($$->lexeme, "+");

                        nodes[nodeCount] = $$;
                        nodeCount++;
                    }
                    | SUB {
                        $$ = newNode();
                        strcpy($$->lexeme, "-");

                        nodes[nodeCount] = $$;
                        nodeCount++;
                    } 
                    ;
            
termo				: termo mult fator {
                        $$ = $2;
                        $$->nodeKind = ExpK;
                        $$->lineNum = lineNum;
                        $$->expKind = OpK;

                        addChild($$, $1);
                        addChild($$, $3);
                        
                    }
                    | fator {$$ = $1;}
                    ;
            
mult				: MULT {
                        $$ = newNode();
                        strcpy($$->lexeme, "*");

                        nodes[nodeCount] = $$;
                        nodeCount++;
                    }
                    | DIV {
                        $$ = newNode();
                        strcpy($$->lexeme, "/");

                        nodes[nodeCount] = $$;
                        nodeCount++;
                    }
                    ;
            
fator				: ABREPARENTESES expressao FECHAPARENTESES  {$$ = $2;}
                    | var {$$ = $1;}
                    | ativacao {$$ = $1;}
                    | NUM { 
                        $$ = newNode();
                        $$->nodeKind = ExpK;
                        $$->lineNum = lineNum;
                        $$->expKind = ConstK;

                        strcpy($$->lexeme, stack[indStack]);
                        indStack--;

                        //strcpy($$->lexeme, auxNome);

                        nodes[nodeCount] = $$;
                        nodeCount++;
                    }
                    ;

ativacao 			: fun_id ABREPARENTESES args FECHAPARENTESES {
                        $$ = $1;
                        $$->nodeKind = ExpK;
                        $$->lineNum = lineNum;
                        $$->expKind = AtivK;
                        addChild($$, $3);
                    }
                    ;
            
args 				: arg_lista {$$ = $1;}
                    | %empty {$$ = NULL;}
                    ;
            
arg_lista			: arg_lista COMMA expressao {
                        if($1 != NULL){
                            $$ = $1;
                            addSibling($$, $3);
                        } else $$ = $3;
                    }
                    | expressao {
                        $$ = $1;
                    }
                    ;			


%%

// Function to show syntax errors
void yyerror(char *s) {
    printf(ANSI_COLOR_YELLOW "ERRO SINTÁTICO: " ANSI_COLOR_RESET ANSI_COLOR_WHITE "\"%s\" ", yytext);
    printf(ANSI_COLOR_YELLOW "LINHA: " ANSI_COLOR_WHITE "%d" ANSI_COLOR_RESET " | %s\n", lineNum, s);
    syntax_errors++;
}

int yylex(void)
{ return (auxError = getToken()); }

NODEPOINTER parse(void)
{ 
    yyparse();
    return syntax_tree;
}