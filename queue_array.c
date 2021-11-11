#include <stdio.h>
#include <stdlib.h>

#include "queue_array.h"

int *init_queue(int size)
{
    int *queue = (int*) malloc(size * sizeof(int));
    if(queue == NULL) exit(0);
    else return queue;
}

void ARRAY_push(int *pusher, int size, int queue[], int v)
{
    queue[((*pusher) % size)] = v;
    (*pusher)++;
    return ;
}

int ARRAY_pop(int *poper, int size, int queue[])
{
    int v = (*poper);
    (*poper)++;
    return queue[v % size];
}

void free_queue(int queue[])
{
    free(queue);
    return ;
}
