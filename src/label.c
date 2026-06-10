#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "label.h"

VECTOR_LABEL *vectorLabel = NULL;

void initializeLabels() {
    vectorLabel = (VECTOR_LABEL *)malloc(sizeof(VECTOR_LABEL));
    vectorLabel->vector = NULL;
    vectorLabel->size = -1;
}

LABEL* createLabelNode(char* id, int address) {
    LABEL* newNode = (LABEL*)malloc(sizeof(LABEL));
    newNode->id = strdup(id);
    newNode->address = address;
    newNode->prox = NULL;
    return newNode;
}

void insertLabel(char* id, int address) {
    LABEL* newNode = createLabelNode(id, address);
    if (vectorLabel->vector == NULL) {
        vectorLabel->vector = newNode;
    } else {
        LABEL* temp = vectorLabel->vector;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = newNode;
    }
    vectorLabel->size++;
}

int getLabelAddress(char* id) {
    LABEL* temp = vectorLabel->vector;
    while (temp != NULL) {
        if (strcmp(temp->id, id) == 0) {
            return temp->address;
        }
        temp = temp->prox;
    }
    return -1; // Label not found
}

void freeLabels() {
    LABEL* temp = vectorLabel->vector;
    while (temp != NULL) {
        LABEL* toFree = temp;
        temp = temp->prox;
        free(toFree->id);
        free(toFree);
    }
    free(vectorLabel);
}

void printLabels(){
    LABEL* aux = vectorLabel->vector;

    printf("\n============= Labels =============\n");
    while (aux != NULL) {
        printf("Label: %s, Address: %d\n", aux->id, aux->address);
        aux = aux->prox;
    }
    printf("==================================\n");
}