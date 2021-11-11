#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int BFS_pop(edge **head, edge **tail)
{
    int v;
    edge *aux = *head;
    v = aux->v;
    if(*head == *tail){
        *head = NULL; 
        *tail = NULL;
    }
    else{
        *head = (*head)->next;
    }
    
    free(aux);
    return v;
}

void BFS_push(edge **head, edge **tail, int v)
{
    edge *aux = (edge*) malloc(sizeof(edge));
    if(aux == NULL) exit(0);

    aux->v = v;
    aux->next = NULL;
    if(*head == NULL){
        *head = aux;
        *tail = aux;
    }
    else{
        (*tail)->next = aux;
        *tail = aux;
    }
}
