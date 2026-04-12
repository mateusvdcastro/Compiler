#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "parser.tab.h"
#include "semantica.h"
#include "codInterm.h"

FILE * fileINPUT = NULL;
FILE * fileCOPY = NULL;
FILE * fileOUTPUT = NULL;

extern int yylex_destroy(void);

Stack lexStack;
int numLine = 1;

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
            printf("%-5d %-20s %-10d %s\n", numLine, "EOF", 0, "");
            break;
        }
        
        // Exibir informações do token
        printf("%-5d %-20s %-10d %s\n", numLine, getTokenName(token), token, yytext ? yytext : "");
        
    } while (token != 0 && token != YYEOF);

    printf("\n=== RESUMO ===\n");
    printf("Total de tokens encontrados: %d\n", tokenCount);
    printf("Número de linhas processadas: %d\n", numLine);

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

    //callOnlyLexicalAnalysis(argv[1]);

    extern int yydebug;
    yydebug = 0; // Defina como 1 para ativar a depuração do Bison

    NODEPOINTER syntaxTree = parse();

    if (syntaxTree == NULL) {
        printf("Erro na análise sintática. A árvore de sintaxe não foi gerada.\n");
        yylex_destroy();
        fclose(fileINPUT);
        return 1;
    } else {
        
        // Criar e inicializar tabela de símbolos
        printf("\n============== ANÁLISE SEMÂNTICA ============== \n");
        Item **symbolTable = startable();
        
        if (symbolTable == NULL) {
            printf("Erro: Não foi possível criar a tabela de símbolos.\n");
            freeTree(syntaxTree);
            yylex_destroy();
            fclose(fileINPUT);
            return 1;
        }
        
        // Executar análise semântica
        analyzeTree(syntaxTree, symbolTable, "global");
        
        // Verificar se houve erros semânticos
        if (semanticError > 0) {
            printf("Total de erros semânticos: %d\n\n", semanticError);
        } else {
            printf("Análise semântica concluída sem erros.\n\n");
        }
        
        // Exibir tabela de símbolos
        printf("============== ÁRVORE DE SINTAXE ============== \n");
        showTree(syntaxTree, 0);


        printable(symbolTable);

        printf("\n============== CODIGO INTERMEDIARIO ============== \n");
        if (semanticError == 0) {
            buildIntermediateCode(syntaxTree, symbolTable, 1);
            printIntermediateCode(stdout);
            freeIntermediateCode();
        } else {
            printf("Geracao de codigo intermediario ignorada devido a erros semanticos.\n\n");
        }

        // Liberar recursos
        destructable(symbolTable);
        freeTree(syntaxTree);
    }

    yylex_destroy();

    if (fileINPUT) fclose(fileINPUT);
    if (fileCOPY) fclose(fileCOPY);
    if (fileOUTPUT) fclose(fileOUTPUT);
    return 0;
}
