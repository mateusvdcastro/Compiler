%{
#include <string.h>
#include "include/parser.h"
#include "include/global.h"

int lineNum = 1;
int yylex(void);

char id[MAXLEXEME];

int firstTime = 1;

int indStack = -1;
char stack[4][MAXLEXEME];
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

"/*"		{
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
            if(strlen(yytext) >= MAXLEXEME){
                printf(ANSI_COLOR_PURPLE "WARNING: Digito muito grande - " ANSI_COLOR_RESET ); 
                yytext[MAXLEXEME-1] = '\0';
                printf("valor reduzido para apenas %s\n", yytext);
            }
        
            
            indStack++;
            strcpy(stack[indStack], yytext);

            return NUM; 
         }

{IDENT} {
            enum yytokentype token = ID;
            
            /* If the ID is longer than the allowed maximum,
            its content will be truncated to fit the language requirements */
            if(strlen(yytext) >= MAXLEXEME){
                printf(ANSI_COLOR_PURPLE "WARNING: ID muito grande - " ANSI_COLOR_RESET ); 
                yytext[MAXLEXEME-1] = '\0';
                printf("nome reduzido para '%s'\n", yytext);
            }

            if(token == ID){
                if(indStack < 3) { // Protect against overflow
                    indStack++;
                    memset(stack[indStack], 0, MAXLEXEME);
                    strcpy(stack[indStack], yytext);
                }
            }
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

":qw" {if(fileINPUT == stdin) return 0;}

.                 {
    printf(ANSI_COLOR_RED "\nERRO LÉXICO: " ANSI_COLOR_RESET ANSI_COLOR_WHITE "\"%s\" ", yytext);
    printf(ANSI_COLOR_RED "LINHA: " ANSI_COLOR_WHITE "%d" ANSI_COLOR_RESET "\n", lineNum);
    lexical_errors++;
    return ERRO;
}

%%


//Function that copies the input file to an extra output file
void copyFunc(FILE* old){
    FILE *new;
    new=fopen("copia.txt","w");
    if (new==NULL){
        printf("Error opening file\n");
        exit(1);
    }

    char letter;
    while((letter = fgetc(old)) != EOF) fprintf(new, "%c", letter);

    fclose(new);
    return;
}

enum yytokentype getToken(void) {
    if (firstTime == 1){
        firstTime = 0;
        yyin = fileINPUT;

        if (fileINPUT == stdin){
            fprintf(fileOUTPUT, "Bem vindo ao compilador de C-!\n");
            fprintf(fileOUTPUT, "Para sair, digite :qw e aperte enter\n(O valor sera identificado como um token para finalizar as entradas)\n");
            fprintf(fileOUTPUT, "Digite o codigo fonte:\n\n");
            fileCOPY = NULL;
        }

        else {
            copyFunc(fileINPUT);
            rewind(fileINPUT); // rewind is used to reset the file pointer to the beginning of the file
            fileCOPY = fopen("copia.txt", "r");
        }

        for (int i = 0; i < 4; i++) {
            memset(stack[i], 0, MAXLEXEME);
        }
    }

    enum yytokentype currentToken;

    currentToken = yylex();
    if (currentToken == ID) strcpy(id, yytext);
    return currentToken;
}