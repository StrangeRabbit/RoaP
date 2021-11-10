#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

#define highPri(a, b) (dist[a] < dist[b])
#define exch(a, b) t = a; a = b;  b = t

/**
 * @brief init heap and position array
 * 
 * @param size size of heap to init
 * @param heap pointer to heap
 * @param hsize size of heap
 * @param free first element free
 * @param position array of positions in the heap
 */
void hinit(unsigned size, int *heap[], int *hsize, int *free, int *position[])
{
    /* allocate heap */
    (*heap) = (int*) malloc(sizeof(int) * size);

    /* allocate and init positions array */
    (*position) = (int*) malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++){
        (*position)[i] = -1;
    }

    /* init hsize and free */
    (*hsize) = size;
    (*free) = 0;

}

/**
 * @brief push vertice to heap
 * 
 * @param v vertice to push
 * @param dist dist of rooms to the source
 * @param queue heap
 * @param hsize size of heap
 * @param free first element free
 * @param position array of positions of vertices in the heap
 */
void push(int v, int dist[], int queue[], int hsize, int *free, int position[])
{
    
    if(((*free) + 1) < hsize){
        /* insert in last position */
        queue[*free] = v;

        /* update position of the v added */
        position[v] = (*free);
        
        /* fix up the element added */
        FixUp(queue, position, (*free), dist);
        (*free)++;
    }
}

/**
 * @brief fix up an element
 * 
 * @param heap heap
 * @param position position of the vertices in the heap
 * @param idx idx of the vertice in the heap to fix up
 * @param dist dist of the rooms to source
 */
void FixUp(int heap[], int position[], int idx, int dist[])
{
    int t;
    /* while parent less prioritary than idx, change it */
    while(idx > 0 && highPri(heap[idx], heap[(idx-1)/2]) ){
        exch(position[heap[idx]], position[heap[(idx-1)/2]]);
        exch(heap[idx], heap[(idx-1)/2]);
        idx = (idx-1)/2;
    }
}

/**
 * @brief fix down a vertice
 * 
 * @param free first position free
 * @param heap heap
 * @param position array with position of vertices in the heap
 * @param idx idx of the vertice to fix down
 * @param dist dist of the rooms to source
 */
void FixDown(int free, int heap[], int position[], int idx, int dist[])
{
    int child, t;
    /* while we dont read the last line, organize childs */
    while(idx * 2 < free - 1){
        child = 2 * idx + 1;
        /* choose the child with highest priority */
        if(child < (free - 1) && highPri(heap[child + 1], heap[child])) child++;
        /* break if priority of parent is correct */
        if(highPri(heap[idx], heap[child])) break;
        exch(position[heap[idx]], position[heap[child]]);
        exch(heap[idx], heap[child]);
        idx = child;
    }
}

/**
 * @brief remove the room with the highest priority
 * 
 * @param heap heap
 * @param position array with the position of rooms in the heap
 * @param dist dist of rooms to the source
 * @param free first item free
 * @return room with the highest priority
 */
int pop(int heap[], int position[], int dist[], int *free)
{
    int t;
    /* exchange the first with last in the heap */
    exch(position[heap[0]], position[heap[(*free) - 1]]);

    /* remove from positions array */
    position[heap[0]] = -1;
    exch(heap[0], heap[(*free) - 1]);

    /* fix down the element we put in first */
    FixDown((*free) - 1, heap, position, 0, dist);
    return heap[--(*free)];
}

/**
 * @brief Get the position of a vertice in the heap
 * 
 * @param position array with positions
 * @param v vertice to get the position
 * @return the position in the heap
 */
int get_pos(int position[], int v)
{
    return position[v];
}
