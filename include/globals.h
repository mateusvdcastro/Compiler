#ifndef _GLOBALS_H_
#define _GLOBALS_H_ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG_MODE 0 // Activate debug mode
#define MAXLEXEME 21 // Maximum lexeme length

extern int flagVerbose; // Flag to activate verbose mode
extern int indStack; // lexeme stack index
extern int lineNum; // line number
extern int lineCount; // line counter
extern int lexical_errors; // lexical errors counter
extern int syntax_errors;
extern char* yytext; // lexeme text
extern char stack[4][MAXLEXEME]; // lexeme stack
extern FILE * fileINPUT; // input file
extern FILE * fileCOPY; // copy of the input file
extern FILE * fileOUTPUT; // output file

// Bring syntax tree types after MAXLEXEME is defined
#include "syntax_tree.h"

// ANSI colors
#define ANSI_COLOR_RED      "\x1b[31m" 
#define ANSI_COLOR_GRAY     "\e[0;37m"
#define ANSI_COLOR_WHITE    "\e[1;37m" 
#define ANSI_COLOR_YELLOW   "\e[0;33m"
#define ANSI_COLOR_RESET    "\e[0m"	
#define ANSI_COLOR_PURPLE   "\e[0;35m"
#define ANSI_COLOR_GREEN    "\e[0;32m"

// Function to get the next token from the input
enum yytokentype getToken(void);

// Function to parse the input
NODEPOINTER parse(void);

#endif