#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

/**
 * @brief inicializes the array that will contain the list
 * @param size size of the array
 * @return returns the queue pointer
 */
int *init_queue(int size)
{
    int *queue = (int *)malloc(size * sizeof(int));
    if (queue == NULL)
        exit(0);
    else
        return queue;
}

/**
 * @brief pushes an int to the queue
 * @param pusher int that will give the index of where to push to
 * @param size size of the array 
 * @param queue array cointaing the stack 
 * @param v int to be pushed to the array 
 */
void ARRAY_push(int *pusher, int size, int queue[], int v)
{
    queue[((*pusher) % size)] = v;
    (*pusher)++;
    return;
}

/**
 * @brief pop an item from the queue 
 * @param poper int that will give the index of where to pop to 
 * @param size size of the array 
 * @param queue array cointaing the stack 
 * @return int that was poped
 */
int ARRAY_pop(int *poper, int size, int queue[])
{
    int v = (*poper);
    (*poper)++;
    return queue[v % size];
}

/**
 * @brief Frees the allocated memory of the stack 
 * @param queue array allocated to cointain the stack
 * 
 */
void free_queue(int queue[])
{
    free(queue);
    return;
}
