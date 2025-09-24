#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "parser.h"

// Function to get token name for display
const char* getTokenName(enum yytokentype token) {
    switch(token) {
        case NUM: return "NUM";
        case SOMA: return "SOMA";
        case SUB: return "SUB";
        case MULT: return "MULT";
        case DIV: return "DIV";
        case INT: return "INT";
        case ID: return "ID";
        case VOID: return "VOID";
        case WHILE: return "WHILE";
        case ELSE: return "ELSE";
        case IF: return "IF";
        case ABREPARENTESES: return "ABREPARENTESES";
        case FECHAPARENTESES: return "FECHAPARENTESES";
        case RETURN: return "RETURN";
        case COMMA: return "COMMA";
        case ABRECHAVES: return "ABRECHAVES";
        case FECHACHAVES: return "FECHACHAVES";
        case SEMICOLON: return "SEMICOLON";
        case ATRIB: return "ATRIB";
        case ABRECOLCHETES: return "ABRECOLCHETES";
        case FECHACOLCHETES: return "FECHACOLCHETES";
        case EQ: return "EQ";
        case NEQ: return "NEQ";
        case LT: return "LT";
        case LET: return "LET";
        case GT: return "GT";
        case GET: return "GET";
        case ERRO: return "ERRO";
        case IFX: return "IFX";
        case YYEOF: return "EOF";
        default: return "UNKNOWN";
    }
}

void callOnlyLexicalAnalysis(char *argv){
    printf("=== ANÁLISE LÉXICA ===\n");
    printf("Arquivo: %s\n\n", argv);
    printf("%-5s %-20s %-10s %s\n", "Linha", "Token", "Valor", "Lexema");
    printf("%-5s %-20s %-10s %s\n", "-----", "--------------------", "----------", "--------");

    enum yytokentype token;
    int tokenCount = 0;
    
    // Loop para obter todos os tokens
    do {
        token = getToken();
        tokenCount++;
        
        if (token == 0 || token == YYEOF) {
            printf("%-5d %-20s %-10d %s\n", lineNum, "EOF", 0, "");
            break;
        }
        
        // Exibir informações do token
        printf("%-5d %-20s %-10d %s\n", lineNum, getTokenName(token), token, yytext ? yytext : "");
        
    } while (token != 0 && token != YYEOF);

    printf("\n=== RESUMO ===\n");
    printf("Total de tokens encontrados: %d\n", tokenCount);
    printf("Número de linhas processadas: %d\n", lineNum);

    if (lexical_errors > 0) {
        printf("Erros léxicos encontrados: %d\n", lexical_errors);
    } else {
        printf("Nenhum erro léxico encontrado.\n");
    }

    // Fechar arquivo
    fclose(fileINPUT);
}

int main (int argc, char *argv[]) {
    if (argc != 2){
        printf("Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }

    // Abrir arquivo de entrada
    fileINPUT = fopen(argv[1], "r");
    if (fileINPUT == NULL) {
        printf("Erro: Não foi possível abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    callOnlyLexicalAnalysis(argv[1]);


    
    return 0;
}