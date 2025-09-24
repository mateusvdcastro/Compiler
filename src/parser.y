%{
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "syntax_tree.h"

enum yytokentype auxError;
%}

/* Token declarations - you should add your actual tokens here */
%token NUM ID ABREPARENTESES FECHAPARENTESES ABRECOLCHETES FECHACOLCHETES
%token ABRECHAVES FECHACHAVES ATRIB COMMA SEMICOLON SOMA SUB MULT DIV
%token EQ NEQ LT GT LET GET INT VOID WHILE ELSE IF RETURN ERRO

%%

/* Grammar rules - this is a minimal example, replace with your actual grammar */
program: /* empty */
       | program statement
       ;

statement: ID
         | NUM  
         | error { yyerror("syntax error"); }
         ;

%%

void yyerror(char *s) {
    printf(ANSI_COLOR_YELLOW "ERRO SINTÁTICO: " ANSI_COLOR_RESET ANSI_COLOR_WHITE "\"%s\" ", yytext);
    printf(ANSI_COLOR_YELLOW "LINHA: " ANSI_COLOR_WHITE "%d" ANSI_COLOR_RESET " | %s\n", lineNum, s);
    syntax_errors++;
}

int yylex(void){
    auxError = getToken();
    
    // Print the token when it's retrieved
    switch(auxError) {
        case NUM: printf("NUM(%s) ", yytext); break;
        case ID: printf("ID(%s) ", yytext); break;
        case ABREPARENTESES: printf("ABREPARENTESES "); break;
        case FECHAPARENTESES: printf("FECHAPARENTESES "); break;
        case ABRECOLCHETES: printf("ABRECOLCHETES "); break;
        case FECHACOLCHETES: printf("FECHACOLCHETES "); break;
        case ABRECHAVES: printf("ABRECHAVES "); break;
        case FECHACHAVES: printf("FECHACHAVES "); break;
        case ATRIB: printf("ATRIB "); break;
        case COMMA: printf("COMMA "); break;
        case SEMICOLON: printf("SEMICOLON "); break;
        case SOMA: printf("SOMA "); break;
        case SUB: printf("SUB "); break;
        case MULT: printf("MULT "); break;
        case DIV: printf("DIV "); break;
        case EQ: printf("EQ "); break;
        case NEQ: printf("NEQ "); break;
        case LT: printf("LT "); break;
        case GT: printf("GT "); break;
        case LET: printf("LET "); break;
        case GET: printf("GET "); break;
        case INT: printf("INT "); break;
        case VOID: printf("VOID "); break;
        case WHILE: printf("WHILE "); break;
        case ELSE: printf("ELSE "); break;
        case IF: printf("IF "); break;
        case RETURN: printf("RETURN "); break;
        case ERRO: printf("ERRO "); break;
        case 0: printf("EOF "); break;
        default: printf("UNKNOWN_TOKEN(%d) ", auxError); break;
    }
    
    return auxError;
}

NODEPOINTER parse(void){
    yyparse();
    return syntaxTree;
}