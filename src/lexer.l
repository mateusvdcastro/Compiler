%{
#include <string.h>
#include "parser.h"
#include "globals.h"

int lineNum = 1;
int yylex(void);

char id[MAXLEXEME];

int firstTime = 1;

int lexical_errors = 0;
%}

%option noyywrap
%option nounput

DIGIT    [0-9]
NUMBER    {DIGIT}+
LETTER     [a-zA-Z]
IDENT     {LETTER}({LETTER}|{DIGIT})*
NEWLINE   \n
WHITESPACE [ \t]+

%%

{WHITESPACE}    { /* ignore whitespace */ }

"/*"	{
          char c, aux = 'x'; 
          do{ 
            c = input();
            if (c == EOF) break;

            if (c == '\n') {
                lineNum++;
            }
            if (c == '*'){
                aux = input();
            }
          } while (aux != '/');
        }

{NEWLINE}    { lineNum++; }

{NUMBER} {
            return NUM; 
         }

{IDENT} {
            enum yytokentype token = ID;
            return token;
         }

"(" {
    return ABREPARENTESES;
   }

")" {
    return FECHAPARENTESES;
   } 

"[" {
    return ABRECOLCHETES;
   }	      
          
          
"]" {
    return FECHACOLCHETES;
   }	      

          
"{" {
    return ABRECHAVES;
   }
          
"}" {
    return FECHACHAVES;	
   }

          
"=" {
    return ATRIB;
  }	
    
"," {
    return COMMA;
  }	
  
";" {
    return SEMICOLON;
  }
  
"+" {
    return SOMA;
   }	
   
"-" {
    return SUB;
   }  
   
"*" {
    return MULT;
   }	
   
"/" {
    return DIV;
   } 

"==" {
    return EQ;
   }

"!=" {
    return NEQ;
    }

"<" {
    return LT;
  }

">" {
    return GT;
  }

"<=" {
        return LET;
      }

">=" {	
        return GET;
      }
    
<<EOF>> {
        return 0;
    }

.   {
    printf(ANSI_COLOR_RED "\nERRO LÉXICO: " ANSI_COLOR_RESET ANSI_COLOR_WHITE "\"%s\" ", yytext);
    printf(ANSI_COLOR_RED "LINHA: " ANSI_COLOR_WHITE "%d" ANSI_COLOR_RESET "\n", lineNum);
    lexical_errors++;
    return ERRO;
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
        printf("Token: %d\n", token); // Apenas para demonstração
    }

    fclose(file);
    return 0;
}