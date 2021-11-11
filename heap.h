#ifndef _HEAP_H_
#define _HEAP_H_

void hinit(unsigned size, int *heap[], int *hsize, int *free, int *position[]);
void HEAP_push(int v, int dist[], int queue[], int hsize, int *free, int position[]);
void FixUp(int heap[], int position[], int idx, int dist[]);
void FixDown(int free, int heap[], int position[], int idx, int dist[]);
int HEAP_pop(int heap[], int position[], int dist[], int *free);
int get_pos(int position[], int v);

#endif