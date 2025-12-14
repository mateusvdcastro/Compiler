%{
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "syntax_tree.h"

#define YYSTYPE NODEPOINTER
#define MAX_NODES 1000

static int yylex(void);
void yyerror (char *s);

NODEPOINTER nodes[MAX_NODES];
NODEPOINTER syntaxTree;

enum yytokentype auxError;

int nodeCount = 0;
int syntax_errors = 0;
%}
	
/* Token declarations - you should add your actual tokens here */
%token NUM ID ABREPARENTESES FECHAPARENTESES ABRECOLCHETES FECHACOLCHETES
%token ABRECHAVES FECHACHAVES ATRIB COMMA SEMICOLON SOMA SUB MULT DIV
%token EQ NEQ LT GT LET GET INT VOID WHILE ELSE IF RETURN

%nonassoc IFX
%nonassoc ELSE

%%

program				: declaration_list {
						//printf("PROGRAM\n");
						syntaxTree = $1;
					}
					;

declaration_list	: declaration_list declaration {
						if ($1 != NULL){
							$$ = $1;
							addSibling($$, $2);
						} else {
							$$ = $2;
						}
						//printf("DECLARATION_LIST\n");
					}
					| declaration {
						//printf("DECLARATION_LIST\n");
						$$ = $1;
					}
					;

declaration			: var_declaration {
						//printf("VAR_DECLARATION\n");
						$$ = $1;
					}
					| fun_declaration {
						//printf("FUN_DECLARATION\n");
						$$ = $1;
					}
					;

var_declaration		: type_specifier ID SEMICOLON {
						//printf("VAR_DECLARATION\n");

						$$ = $1;
						$$->nodeKind = StmtK;
						$$->lineNum = lineNum;
						$$->stmtKind = VarDeclK;

						NODEPOINTER aux = newNode();

						strcpy(aux->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL); // Pop ID

						addChild($$, aux); // ID

						nodes[nodeCount++] = $$;
					}
					| type_specifier error SEMICOLON {
						yyerrok;
						//printf("VAR_DECLARATION ERROR RECOVERED\n");
						//if ($1 != NULL) freeTree($1);
						$$ = NULL;

					}
					| type_specifier ID ABRECOLCHETES NUM FECHACOLCHETES SEMICOLON {
						//printf("VAR_DECLARATION ARRAY\n");

						$$ = $1;
						$$->nodeKind = StmtK;
						$$->lineNum = lineNum;
						$$->stmtKind = VetDeclK;

						NODEPOINTER aux = newNode();
						NODEPOINTER aux2 = newNode();

						strcpy(aux->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL); // Pop ID

						strcpy(aux2->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL); // Pop NUM


						addChild($$, aux2); // NUM
						addChild($$, aux); // ID

						nodes[nodeCount++] = $$;
					}
					| type_specifier error FECHACOLCHETES SEMICOLON {
						yyerrok;
						//printf("VAR_DECLARATION ERROR RECOVERED\n");
						//if ($1 != NULL) freeTree($1);
						$$ = NULL;
					}
					;

type_specifier		: INT {
						$$ = newNode();
						strcpy($$->lexeme, "INT");
						$$->lineNum = lineNum;

						nodes[nodeCount++] = $$;
					}
					| VOID {
						$$ = newNode();
						strcpy($$->lexeme, "VOID");
						$$->lineNum = lineNum;

						nodes[nodeCount++] = $$;
					}
					;

fun_declaration		: type_specifier fun_id ABREPARENTESES params FECHAPARENTESES compound_decl {
						printf("FUN_DECLARATION\n");

						$$ = $1;

						addChild($$, $4); // params
						addChild($$, $2); // fun_id
						addChild($$, $6); // compound_decl

						$$->nodeKind = StmtK;
						$$->stmtKind = FunDeclK;
					}
					;

fun_id				: ID {
						$$ = newNode();

						strcpy($$->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL);

						$$->lineNum = lineNum;

						nodes[nodeCount++] = $$;
					}
					;
params 				: param_list {
						$$ = $1;
					}
					| VOID {
						$$ = newNode();
						$$->nodeKind = StmtK;
						$$->lineNum = lineNum;
						$$->stmtKind = ParamVoid;
						strcpy($$->lexeme, "VOID");

						nodes[nodeCount++] = $$;
					}
					;
param_list			: param_list COMMA param {
						if ($1 != NULL){
							$$ = $1;
							addSibling($$, $3);
						} else {
							$$ = $3;
						}
					}
					| param {
						$$ = $1;
					}
					;
param				: type_specifier ID {
						$$ = $1;
						$$->nodeKind = StmtK;
						$$->lineNum = lineNum;
						$$->stmtKind = VarParamK;
						NODEPOINTER aux = newNode();
						strcpy($$->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL);

						addChild($$, aux);
						nodes[nodeCount++] = $$;

					}
					| type_specifier ID ABRECOLCHETES FECHACOLCHETES {
						//printf("PARAMETER ARRAY\n");
						$$ = $1;
						$$->nodeKind = StmtK;
						$$->lineNum = lineNum;
						$$->stmtKind = VetParamK;
						NODEPOINTER aux = newNode();

						strcpy($$->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL);

						addChild($$, aux);
						nodes[nodeCount++] = $$;
					}
					;

compound_decl		: ABRECHAVES local_declarations statement_list FECHACHAVES {
						//printf("COMPOUND_DECLARATION\n");
						if ($2 != NULL){
							$$ = $2;
							addSibling($$, $3);
						} else {
							$$ = $3;
						}
					}
					| ABRECHAVES error FECHACHAVES {
						yyerrok;
						$$ = NULL;
					}
					;

local_declarations	: local_declarations var_declaration {
						if ($1 != NULL){
							$$ = $1;
							addSibling($$, $2);
						} else {
							$$ = $2;
						}
					}
					| %empty {
						$$ = NULL;
					}
					;

statement_list		: statement_list statement {
						if ($1 != NULL){
							$$ = $1;
							addSibling($$, $2);
						} else {
							$$ = $2;
						}
					}
					| %empty {
						$$ = NULL;
					}
					;

statement			: expression_decl {
						//printf("EXPRESSION_DECLARATION\n");
						$$ = $1;
					} | compound_decl {
						//printf("COMPOUND_DECLARATION\n");
						$$ = $1;
					} | selection_decl {
						//printf("SELECTION_DECLARATION\n");
						$$ = $1;
					} | iteration_decl {
						//printf("ITERATION_DECLARATION\n");
						$$ = $1;
					} | return_decl {
						//printf("RETURN_DECLARATION\n");
						$$ = $1;
					}
					;

expression_decl		: expression SEMICOLON {
						//printf("EXPRESSION_DECLARATION\n");
						$$ = $1;
					} | SEMICOLON {
						$$ = NULL;
					} | error SEMICOLON {
						yyerrok;
						//printf("EXPRESSION_DECLARATION ERROR RECOVERED\n");
						$$ = NULL;
					}
					;

selection_decl		: IF ABREPARENTESES expression FECHAPARENTESES statement %prec IFX {
						//printf("SELECTION_DECLARATION\n");

						$$ = newNode();
						strcpy($$->lexeme, "IF");
						$$->nodeKind = StmtK;
						$$->lineNum = lineNum;
						$$->stmtKind = IfK;

						addChild($$, $3);
						addChild($$, $5);

						nodes[nodeCount++] = $$;
					}
					| IF ABREPARENTESES expression FECHAPARENTESES statement ELSE statement {
						//printf("SELECTION_DECLARATION\n");

						$$ = newNode();
						strcpy($$->lexeme, "IF");
						$$->nodeKind = StmtK;
						$$->lineNum = lineNum;
						$$->stmtKind = IfK;

						addChild($$, $3);
						addChild($$, $5);
						addChild($$, $7);

						nodes[nodeCount++] = $$;
					}
					| IF ABREPARENTESES error FECHAPARENTESES statement %prec IFX {
						yyerrok;
						$$ = NULL;
					}
					| IF ABREPARENTESES error FECHAPARENTESES statement ELSE statement {
						yyerrok;
						$$ = NULL;
					}
					;

iteration_decl		: WHILE ABREPARENTESES expression FECHAPARENTESES statement {
						printf("ITERATION_DECLARATION\n");

						$$ = newNode();
						strcpy($$->lexeme, "WHILE");
						$$->nodeKind = StmtK;
						$$->lineNum = lineNum;
						$$->stmtKind = WhileK;

						addChild($$, $3);
						addChild($$, $5);

						nodes[nodeCount++] = $$;
					}
					| WHILE ABREPARENTESES error FECHAPARENTESES statement {
						yyerrok;
						$$ = NULL;
					}
					| WHILE error statement {
						yyerrok;
						$$ = NULL;
					}
					;

return_decl			: RETURN SEMICOLON {
						$$ = newNode();
						$$->nodeKind = StmtK;
						$$->lineNum = lineNum;
						$$->stmtKind = ReturnVoidK;
						strcpy($$->lexeme, "ReturnVoidK");
						nodes[nodeCount++] = $$;
					} | RETURN expression SEMICOLON {
						$$ = newNode();
						$$->nodeKind = StmtK;
						$$->lineNum = lineNum;
						$$->stmtKind = ReturnInK;

						strcpy($$->lexeme, "ReturnInK");

						addChild($$, $2);

						nodes[nodeCount++] = $$;
					}
					;

expression			: var ATRIB expression {
						$$ = newNode();
						strcpy($$->lexeme, "=");
						$$->nodeKind = ExpK;
						$$->lineNum = lineNum;
						$$->expKind = AssignK;

						addChild($$, $1);
						addChild($$, $3);

						//printf("EXPRESSION ATRIB\n");
						nodes[nodeCount++] = $$;
					}
					| simple_expression {
						$$ = $1;
					}
					;

var					: ID {
						$$ = newNode();
						$$->nodeKind = ExpK;
						$$->lineNum = lineNum;
						$$->expKind = IdK;

						strcpy($$->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL);

						nodes[nodeCount++] = $$;
					}
					| ID ABRECOLCHETES expression FECHACOLCHETES {
						$$ = newNode();

						$$->nodeKind = ExpK;
						$$->lineNum = lineNum;
						$$->expKind = VetK;

						strcpy($$->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL);
						
						addChild($$, $3);

						nodes[nodeCount++] = $$;
					}
					;

simple_expression	: simple_expression relational sum_expression {
						$$ = $2;
						$$->nodeKind = ExpK;
						$$->lineNum = lineNum;
						$$->expKind = OpRel;
						addChild($$, $1);
						addChild($$, $3);
					}
					| sum_expression {
						$$ = $1;
					}
					;

relational			: relational_operand {
						$$ = $1;
					}
					;

relational_operand : EQ {
						$$ = newNode();
						strcpy($$->lexeme, "==");
						nodes[nodeCount++] = $$;
					}
					| NEQ {
						$$ = newNode();
						strcpy($$->lexeme, "!=");
						nodes[nodeCount++] = $$;
					} | LT {
						$$ = newNode();
						strcpy($$->lexeme, "<");
						nodes[nodeCount++] = $$;
					} | GT {
						$$ = newNode();
						strcpy($$->lexeme, ">");
						nodes[nodeCount++] = $$;
					} | LET {
						$$ = newNode();
						strcpy($$->lexeme, "<=");
						nodes[nodeCount++] = $$;
					} | GET {
						$$ = newNode();
						strcpy($$->lexeme, ">=");
						nodes[nodeCount++] = $$;
					}
					;

sum_expression		: sum_expression sum term {
						$$ = $2;
						$$->nodeKind = ExpK;
						$$->lineNum = lineNum;
						$$->expKind = OpK;

						addChild($$, $1);
						addChild($$, $3);
					}
					| term {
						$$ = $1;
					}
					;

sum					: SOMA {
						$$ = newNode();
						strcpy($$->lexeme, "+");
						nodes[nodeCount++] = $$;
					} | SUB {
						$$ = newNode();
						strcpy($$->lexeme, "-");
						nodes[nodeCount++] = $$;
					}
					;

term				: term mult factor {
						$$ = $2;
						$$->nodeKind = ExpK;
						$$->lineNum = lineNum;
						$$->expKind = OpK;
						addChild($$, $1);
						addChild($$, $3);
					} | factor {
						$$ = $1;
					}
					;	

mult				: MULT {
						$$ = newNode();

						strcpy($$->lexeme, "*");

						nodes[nodeCount++] = $$;
					} | DIV {
						$$ = newNode();

						strcpy($$->lexeme, "/");

						nodes[nodeCount++] = $$;
					}
					;

factor				: ABREPARENTESES expression FECHAPARENTESES {
						$$ = $2;
					} | var {
						$$ = $1;
					} | activation {
						$$ = $1;
					} | NUM {
						$$ = newNode();
						$$->nodeKind = ExpK;
						$$->lineNum = lineNum;
						$$->expKind = ConstK;

						pop(&lexStack, $$->lexeme);
						printf("FACTOR NUM: %s\n", $$->lexeme);

						nodes[nodeCount++] = $$;
					}
					;

activation			: fun_id ABREPARENTESES args FECHAPARENTESES {
						//printf("ACTIVATION\n");
						$$ = $1;
						$$->nodeKind = ExpK;
						$$->lineNum = lineNum;
						$$->expKind = AtivK;
						addChild($$, $3);
					}
					;

args				: arg_list {
						$$ = $1;
					} | %empty {
						$$ = NULL;
					}
					;

arg_list			: arg_list COMMA expression {
						if ($1 != NULL){
							$$ = $1;
							addSibling($$, $3);
						} else {
							$$ = $3;
						}

						//printf("ARG_LIST COMMA\n");
					}
					| expression {
						$$ = $1;
						//printf("ARG_LIST EXPRESSION\n");
					}
					;
%%

void yyerror (char *s){
	printf("\n" ANSI_COLOR_RED "ERRO SINTATICO, LINHA: %d", lineNum);
	printf(ANSI_COLOR_RESET);
	printf(": token inesperado '%s' (código: %d)", yytext, auxError);
	
	switch(auxError){
		case NUM:
			printf(": '%s' não era esperado (NUM)", yytext);
			break; 
		case SOMA:
			printf(": '%s' não era esperado (SOMA)", yytext);
			break;
		case SUB:
			printf(": '%s' não era esperado (SUB)", yytext);
			break;
		case MULT:
			printf(": '%s' não era esperado (MULT)", yytext);
			break;
		case DIV:
			printf(": '%s' não era esperado (DIV)", yytext);
			break;
		case INT:
			printf(": '%s' não era esperado (INT)", yytext);
			break;
		case ID:
			printf(": '%s' não era esperado (ID)", yytext);
			break;
		case VOID:
			printf(": '%s' não era esperado (VOID)", yytext);
			break;
		case WHILE:
			printf(": '%s' não era esperado (WHILE)", yytext);
			break;
		case ELSE:
			printf(": '%s' não era esperado (ELSE)", yytext);
			break;
		case IF:
			printf(": '%s' não era esperado (IF)", yytext);
			break;
		case ABREPARENTESES:
			printf(": '%s' não era esperado (ABREPARENTESES)", yytext);
			break;
		case FECHAPARENTESES:
			printf(": '%s' não era esperado (FECHAPARENTESES)", yytext);
			break;
		case RETURN:
			printf(": '%s' não era esperado (RETURN)", yytext);
			break;
		case COMMA:
			printf(": '%s' não era esperado (COMA)", yytext);
			break;
		case ABRECHAVES:
			printf(": '%s' não era esperado (ABRECHAVES)", yytext);
			break;
		case FECHACHAVES:
			printf(": '%s' não era esperado (FECHACHAVES)", yytext);
			break;
		case SEMICOLON:
			printf(": '%s' não era esperado (SEMICOLON)", yytext);
			break;
		case ATRIB:
			printf(": '%s' não era esperado (ATRIB)", yytext);
			break;
		case ABRECOLCHETES:
			printf(": '%s' não era esperado (ABRECOLCHETES)", yytext);
			break;
		case FECHACOLCHETES:
			printf(": '%s' não era esperado (FECHACOLCHETES)", yytext);
			break;
		case EQ:
			printf(": '%s' não era esperado (EQ)", yytext);
			break;
		case NEQ:
			printf(": '%s' não era esperado (NEQ)", yytext);
			break;
		case LT:
			printf(": '%s' não era esperado (LT)", yytext);
			break;
		case LET:
			printf(": '%s' não era esperado (LET)", yytext);
			break;
		case GT:
			printf(": '%s' não era esperado (GT)", yytext);
			break;
		case GET:
			printf(": '%s' não era esperado (GET)", yytext);
			break;
	}
	printf("\n");

    syntax_errors++;
	clearStack(&lexStack);
	
	//Desaloca os nos ate o momento
	// Don't free individual nodes - they may share pointers (siblings/children)
	// causing double-free errors. Set nodeCount to 0 to reset tracking.
	//nodeCount = 0;
	//syntaxTree = NULL;

}

int yylex(void){
    auxError = getToken();
    return auxError;
}

NODEPOINTER parse(void){
    yyparse();
    return syntaxTree;
}