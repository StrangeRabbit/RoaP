#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

#define highPri(a, b) (dist[a] < dist[b])
#define exch(a, b) int t = a; a = b;  b = t

void hinit(unsigned size, int *heap[], int *hsize, int *free)
{
    (*heap) = (int*) malloc(sizeof(int) * size);
    (*hsize) = size;
    (*free) = 0;
}

void push(int v, int dist[], int queue[], int hsize, int *free)
{
    if(((*free) + 1) < hsize){
        queue[*free] = v;
        FixUp(queue, (*free), dist);
        (*free)++;
    }
}

void FixUp(int heap[], int idx, int dist[])
{
    while(idx > 0 && highPri(heap[idx], heap[(idx-1)/2]) ){
        exch(heap[idx], heap[(idx-1)/2]);
        idx = (idx-1)/2;
    }
}

void FixDown(int free, int heap[], int idx, int dist[])
{
    int child;
    while(idx * 2 < free - 1){
        child = 2 * idx + 1;

        if(child < (free - 1) && highPri(heap[child + 1], heap[child])) child++;
        if(highPri(heap[idx], heap[child])) break;
        exch(heap[idx], heap[child]);
        idx = child;
    }
}

int pop(int heap[], int dist[], int *free)
{
    exch(heap[0], heap[(*free) - 1]);
    FixDown((*free) - 1, heap, 0, dist);
    return heap[--(*free)];
}

int get_pos(int heap[], int v, int free)
{
    unsigned int i;
    for(i = 0; i < free; i++){
        if(heap[i] == v)
            return i;
    }
    return -1;
}