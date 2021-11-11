#ifndef _QUEUE_ARRAY_
#define _QUEUE_ARRAY_

int *init_queue(int size);
void push(int *pusher, int size, int queue[], int v);
int pop(int *poper, int size, int queue[], int v);
void free_queue(int queue[]);

#endif