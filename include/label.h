#ifndef _LABEL_H_
#define _LABEL_H_

typedef struct label {
    char* id;
    int address;
    struct label *prox;
} LABEL;

typedef struct vectorLabel{
    LABEL *vector;
    int size;
} VECTOR_LABEL;

extern VECTOR_LABEL *vectorLabel;

void initializeLabels();
LABEL* createLabelNode(char* id, int address);
void insertLabel(char* id, int address);
int getLabelAddress(char* id);
void freeLabels();
void printLabels();

#endif