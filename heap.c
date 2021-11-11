#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

#define highPri(a, b) (dist[a] < dist[b])
#define exch(a, b) t = a; a = b;  b = t

void hinit(unsigned size, int *heap[], int *hsize, int *free, int *position[])
{
    (*heap) = (int*) malloc(sizeof(int) * size);
    (*position) = (int*) malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++){
        (*position)[i] = -1;
    }
    (*hsize) = size;
    (*free) = 0;

}

void HEAP_push(int v, int dist[], int queue[], int hsize, int *free, int position[])
{
    if(((*free) + 1) < hsize){
        queue[*free] = v;
        position[v] = (*free);
        FixUp(queue, position, (*free), dist);
        (*free)++;
    }
}

void FixUp(int heap[], int position[], int idx, int dist[])
{
    int t;
    while(idx > 0 && highPri(heap[idx], heap[(idx-1)/2]) ){
        exch(position[heap[idx]], position[heap[(idx-1)/2]]);
        exch(heap[idx], heap[(idx-1)/2]);
        idx = (idx-1)/2;
    }
}

void FixDown(int free, int heap[], int position[], int idx, int dist[])
{
    int child, t;
    while(idx * 2 < free - 1){
        child = 2 * idx + 1;

        if(child < (free - 1) && highPri(heap[child + 1], heap[child])) child++;
        if(highPri(heap[idx], heap[child])) break;
        exch(position[heap[idx]], position[heap[child]]);
        exch(heap[idx], heap[child]);
        idx = child;
    }
}

int HEAP_pop(int heap[], int position[], int dist[], int *free)
{
    int t;
    exch(position[heap[0]], position[heap[(*free) - 1]]);
    position[heap[0]] = -1;
    exch(heap[0], heap[(*free) - 1]);
    FixDown((*free) - 1, heap, position, 0, dist);
    return heap[--(*free)];
}

int get_pos(int position[], int v)
{
    return position[v];
}
