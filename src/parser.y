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
%token EQ NEQ LT GT LET GET INT VOID WHILE ELSE IF RETURN ERRO

%nonassoc IFX
%nonassoc ELSE

%%

program				: declaration_list {

					}
					;

declaration_list	: declaration_list declaration {

					}
					| declaration {

					}
					;

declaration			: var_declaration {

					}
					| fun_declaration {

					}
					;

var_declaration		: type_specifier ID SEMICOLON {

					}
					| type_specifier ID ABRECOLCHETES NUM FECHACOLCHETES SEMICOLON {

					}
					;

type_specifier		: INT {

					}
					| VOID {

					}
					;

fun_declaration		: type_specifier fun_id ABREPARENTESES params FECHAPARENTESES compound_decl {
						printf("FUN_DECLARATION\n");
					}
					;

fun_id				: ID {

					}
					;

params 				: param_list {

					}
					| VOID {

					}
					;

param_list			: param_list COMMA param {

					}
					| param {

					}
					;

param				: type_specifier ID {

					}
					| type_specifier ID ABRECOLCHETES FECHACOLCHETES {

					}
					;

compound_decl		: ABRECHAVES local_declarations statement_list FECHACHAVES {
						printf("COMPOUND_DECLARATION\n");
					}
					;

local_declarations	: local_declarations var_declaration {

					}
					| %empty {

					}
					;

statement_list		: statement_list statement {

					}
					| %empty {

					}
					;

statement			: expression_decl {

					} | compound_decl {

					} | selection_decl {

					} | iteration_decl {

					} | return_decl {

					}
					;

expression_decl		: expression SEMICOLON {

					} | SEMICOLON {

					}
					;

selection_decl		: IF ABREPARENTESES expression FECHAPARENTESES statement %prec IFX {

					}
					| IF ABREPARENTESES expression FECHAPARENTESES statement ELSE statement {

					}
					;

iteration_decl		: WHILE ABREPARENTESES expression FECHAPARENTESES statement {

					}
					;

return_decl			: RETURN SEMICOLON {

					} | RETURN expression SEMICOLON {

					}
					;

expression			: var ATRIB expression {

					}
					| simple_expression {

					}
					;

var					: ID {
						
					}
					| ID ABRECOLCHETES expression FECHACOLCHETES {

					}
					;

simple_expression	: simple_expression relational sum_expression {

					}
					| sum_expression {

					}
					;

relational			: relational_operand {

					}
					;

relational_operand : EQ {

					}
					| NEQ {

					} | LT {

					} | GT {

					} | LET {

					} | GET {

					}
					;

sum_expression		: sum_expression sum term {

					}
					| term {

					}
					;

sum					: SOMA {

					} | SUB {

					}
					;

term				: term mult factor {

					} | factor {

					}
					;	

mult				: MULT {

					} | DIV {

					}
					;

factor				: ABREPARENTESES expression FECHAPARENTESES {

					} | var {

					} | activation {

					} | NUM {

					}
					;

activation			: fun_id ABREPARENTESES args FECHAPARENTESES {

					}
					;

args				: arg_list {

					} | %empty {

					}
					;

arg_list			: arg_list COMMA expression {
						printf("ARG_LIST COMMA\n");
					}
					| expression {
						printf("ARG_LIST EXPRESSION\n");
					}
					;
%%

void yyerror (char *s){
	printf("\n" ANSI_COLOR_RED "ERRO SINTATICO, LINHA: %d", lineNum);
	printf(ANSI_COLOR_RESET);
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
		case ERRO:
			printf(": '%s' não era esperado (ERRO)", yytext);
			break;
	}
	printf("\n");

    syntax_errors++;
	
	//Desaloca os nos ate o momento
	for(int i = 0; i < nodeCount; i++){
		free(nodes[i]);
	} 
	syntaxTree = NULL;

}

int yylex(void){
    auxError = getToken();
    return auxError;
}

NODEPOINTER parse(void){
    yyparse();
    return syntaxTree;
}