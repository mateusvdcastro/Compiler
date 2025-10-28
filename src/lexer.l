%{
#include <string.h>
#include "parser.h"
#include "globals.h"

int lineNum = 1;
int yylex(void);

char id[MAXLEXEME];

int verifyReservedWord(enum yytokentype *token);

int firstTime = 1;

int lexical_errors = 0;

int isFull(Stack *lexStack);
int isEmpty(Stack *lexStack);

void initStack(Stack *lexStack) {
    lexStack->top = -1;
}

void push(Stack *lexStack, char* lexeme) {
    if (isFull(lexStack)) {
        printf("Stack Lexeme Overflow\n");
        return;
    }
    lexStack->top++;
    strcpy(lexStack->stack[lexStack->top], lexeme);

    printf("Pushed lexeme to lexeme stack: %s\n", lexeme);
}

void pop(Stack *lexStack, char* lexeme) {
    if (isEmpty(lexStack)) {
        printf("Stack Lexeme Underflow\n");
        return;
    }
    strcpy(lexeme, lexStack->stack[lexStack->top]);
    lexStack->top--;
    printf("Popped lexeme from lexeme stack: %s\n", lexeme);
}

int isFull(Stack *lexStack) {
    return lexStack->top == 3;
}

int isEmpty(Stack *lexStack) {
    return lexStack->top == -1;
}

%}

%option noyywrap

DIGIT    [0-9]
NUMBER    {DIGIT}+
LETTER     [a-zA-Z]
IDENT     {LETTER}({LETTER}|{DIGIT})*
NEWLINE   \r?\n
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
            push(&lexStack, yytext);

            return NUM; 
         }

{IDENT} {
            enum yytokentype token;

            if(!verifyReservedWord(&token)){
                token = ID;
            }

            if (token == ID) {
                bzero(lexStack.stack[lexStack.top + 1], MAXLEXEME);
                push(&lexStack, yytext);
            };

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

int verifyReservedWord(enum yytokentype *token){
  char aux[20];
  int flag = 0;
  
  if(strcmp(yytext, "if") == 0){
      strcpy(aux, "if");
      *token = IF;
      flag =  1;
  }
  else if(strcmp(yytext, "int") == 0){
      strcpy(aux, "int");
      *token = INT;
      flag =  1;
  }
  else if(strcmp(yytext, "else") == 0){
      strcpy(aux, "else");
      *token = ELSE;
      flag =  1;
  }
  else if(strcmp(yytext, "return") == 0){
      strcpy(aux, "return");
      *token = RETURN;
      flag =  1;
  }
  else if(strcmp(yytext, "void") == 0){
      strcpy(aux, "void");
      *token = VOID;
      flag =  1;
  }
  else if(strcmp(yytext, "while") == 0){
      strcpy(aux, "while");
      *token = WHILE;
      flag =  1;
  }
  return flag;
}

enum yytokentype getToken(void){
    yyin = fileINPUT;

    if (firstTime) {
        
        initStack(&lexStack);

        for (int i = 0; i < 4; i++){
          bzero(lexStack.stack[i], MAXLEXEME);
        }
    }

    firstTime = 0;

    enum yytokentype currentToken;

    currentToken = yylex();

    if(currentToken == ID) strcpy(id, yytext);

    return currentToken;
}