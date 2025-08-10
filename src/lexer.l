%{
#include "include/parser.h"

int lineNum = 1;
int yylex(void);
%}

%option noyywrap

DIGIT    [0-9]
NUMBER    {DIGIT}+
LETTER     [a-zA-Z]
IDENT     {LETTER}({LETTER}|{DIGIT})*
NEWLINE   \n
WHITESPACE [ \t]+

%x COMMENT

%%

"else"            { return ELSE; }
"if"              { return IF; }
"int"             { return INT; }
"return"          { return RETURN; }
"void"            { return VOID; }
"while"           { return WHILE; }

"+"               { return PLUS; }
"-"               { return MINUS; }
"*"               { return MULT; }
"/"               { return DIV; }
"<"               { return SMAL; }
"<="              { return SMALEQ; }
">"               { return GREAT; }
">="              { return GREATEQ; }
"=="              { return EQ; }
"!="              { return DIFF; }
"="               { return ASSIGN; }
";"               { return SEMICOL; }
","               { return COMMA; }
"("               { return LPAREN; }
")"               { return RPAREN; }
"["               { return LBRACKET; }
"]"               { return RBRACKET; }
"{"               { return LBRACE; }
"}"               { return RBRACE; }

"/*"              { BEGIN(COMMENT); }
<COMMENT>"*/"     { BEGIN(INITIAL); }
<COMMENT>\n       { lineNum++; }
<COMMENT>.        { /* ignore comment content */ }

"//".*            { /* ignore single line comment */ }

{NUMBER}          { return NUM; }
{IDENT}           { return ID; }

{WHITESPACE}      { /* Ignore */ }
{NEWLINE}         { lineNum++; }

.                 {
    fprintf(stderr, "ERRO LÉXICO: %s LINHA: %d\n", yytext, lineNum);
    return ERROR;
}

%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s arquivo.*\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    yyin = file;
    
    int token;
    while ((token = yylex()) != 0) {
        // Continue processando todos os tokens
        // Erros já são tratados na função yylex()
    }

    fclose(file);
    return 0;
}