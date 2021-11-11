#include <stdio.h>
#include <stdlib.h>

#include "queue_array.h"

int *init_queue(int size)
{
    int *queue = (int*) malloc(size * sizeof(int));
    if(queue == NULL) exit(0);
    else return queue;
}

void push(int *pusher, int size, int queue[], int v)
{
    queue[((*pusher)++ % size)] = v;
    return ;
}

int pop(int *poper, int size, int queue[], int v)
{
    return queue[(*poper)++ % size];
}

void free_queue(int queue[])
{
    free(queue);
    return ;
}
