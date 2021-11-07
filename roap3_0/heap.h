#ifndef _HEAP_H_
#define _HEAP_H_

void hinit(unsigned size, int queue[], int *hsize, int *free);
void push(int v, int dist[], int queue[], int hsize, int *free);
void FixUp(int heap[], int idx, int dist[]);
void FixDown(int free, int heap[], int idx, int dist[]);
int pop(int heap[], int dist[], int *free);
int get_pos(int heap[], int v, int free);

#endif