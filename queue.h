#ifndef _QUEUE_ARRAY_
#define _QUEUE_ARRAY_

int *init_queue(int size);
void ARRAY_push(int *pusher, int size, int queue[], int v);
int ARRAY_pop(int *poper, int size, int queue[]);
void free_queue(int queue[]);

#endif