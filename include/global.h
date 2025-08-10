#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEXEMA 21 // Tamanho máximo do lexema

// Cores em ANSI
#define ANSI_COLOR_RED      "\x1b[31m" 
#define ANSI_COLOR_GRAY     "\e[0;37m"
#define ANSI_COLOR_WHITE    "\e[1;37m" 
#define ANSI_COLOR_RESET    "\e[0m"	
#define ANSI_COLOR_PURPLE   "\e[0;35m"
#define ANSI_COLOR_GREEN    "\e[0;32m"

// Variáveis globais
extern int lineNum;
extern FILE *yyin, *yyout;
extern char *yytext;

#endif