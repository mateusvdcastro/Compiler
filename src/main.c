#include "include/global.h"
#include "include/syntax_tree.h"
#include "include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// External declarations
extern NODEPOINTER syntax_tree;
extern int syntax_errors;
extern int yyparse(void);
extern FILE *yyin;

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Usage: %s [filename]\n", argv[0]);
        return 1;
    }
    
    // Initialize global variables
    syntax_errors = 0;
    syntax_tree = NULL;
    fileOUTPUT = stdout;
    
    if (argc == 2) {
        // File input mode
        fileINPUT = fopen(argv[1], "r");
        if (fileINPUT == NULL) {
            printf("Error: Cannot open file '%s'\n", argv[1]);
            return 1;
        }
    } else {
        // Interactive mode
        fileINPUT = stdin;
    }
    
    // Parse the input
    yyparse();
    NODEPOINTER tree = syntax_tree;
    
    // Display results
    if (syntax_errors == 0) {
        printf("\nParsing completed successfully!\n");
        if (tree != NULL) {
            printf("\nSyntax Tree:\n");
            printf("=============\n");
            showTree(tree, 0);
        }
    } else {
        printf("\nParsing completed with %d error(s).\n", syntax_errors);
    }
    
    // Cleanup
    if (fileINPUT != stdin && fileINPUT != NULL) {
        fclose(fileINPUT);
    }
    if (fileCOPY != NULL) {
        fclose(fileCOPY);
    }
    if (tree != NULL) {
        freeTree(tree);
    }
    
    return syntax_errors > 0 ? 1 : 0;
}
