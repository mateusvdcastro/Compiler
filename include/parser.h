#ifndef _PARSER_H_
#define _PARSER_H_

#include "global.h"
#include <stdio.h>

extern char* yytext;
extern FILE* yyin;

typedef enum
    /* book-keeping tokens */
   {ENDOFFILE = 256, ERROR = 256,

    /* reserved words */
    // if  else  int  return  void  while
    IF, ELSE, INT, RETURN, VOID, WHILE,

    /* multicharacter tokens */
    // ID  NUM
    ID, NUM,

    /* Símbolos especiais */ 
    // +  -  *  /  <  <=  >  >=  ==  !=  =  ;  ,  (  )  [  ]  {  }  /*  */
    PLUS, MINUS, MULT, DIV, SMAL, SMALEQ, GREAT, GREATEQ, EQ, DIFF, ASSIGN, SEMICOL, COMMA, LPAREN, RPAREN, LBRACKET, RBRACKET, LBRACE, RBRACE, BEGCOMM, CLOSCOMM
} TokenType;

#endif