#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

#define highPri(a, b) (dist[a] < dist[b])
#define exch(a, b) \
    t = a;         \
    a = b;         \
    b = t

/**
 * @brief inicializes an array to contain the inderect heap 
 * @param size size the array need to have
 * @param heap pointer that will be pointed to the array 
 * @param hsize pointer to a int cointaing the size of the heap 
 * @param free pointer to int containing the number of element already freed
 * @param position pointer an array that cointain the position of a vertice in an heap 
 * 
 */
void hinit(unsigned size, int *heap[], int *hsize, int *free, int *position[])
{
    (*heap) = (int *)malloc(sizeof(int) * size);
    (*position) = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        (*position)[i] = -1;
    }
    (*hsize) = size;
    (*free) = 0;
}

/**
 * @brief pushes a vertice to the heap 
 * @param vertice to be pushed to the heap 
 * @param dist array cointain the priority of the vertice
 * @param queue array containing the queue
 * @param hsize is the size of the heap 
 * @param free int to zone where to free
 * @param position array containing the heap position on the heap 
 */
void HEAP_push(int v, int dist[], int queue[], int hsize, int *free, int position[])
{
    if (((*free) + 1) < hsize)
    {
        queue[*free] = v;
        position[v] = (*free);
        FixUp(queue, position, (*free), dist);
        (*free)++;
    }
}

/**
 * @brief Fixes up a position of vertice in the heap
 * @param heap array cointain the heap
 * @param position array containing the position of a vertice in the heap 
 * @param idx index of the vertice to receive the fix up
 * @param dist priority of the vertice
 */
void FixUp(int heap[], int position[], int idx, int dist[])
{
    int t;
    while (idx > 0 && highPri(heap[idx], heap[(idx - 1) / 2]))
    {
        exch(position[heap[idx]], position[heap[(idx - 1) / 2]]);
        exch(heap[idx], heap[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

/**
 * @brief Fixes down a position of vertice in the heap
 * @param heap array cointain the heap
 * @param position array containing the position of a vertice in the heap 
 * @param idx index of the vertice to receive the fix up
 * @param dist priority of the vertice
 */
void FixDown(int free, int heap[], int position[], int idx, int dist[])
{
    int child, t;
    while (idx * 2 < free - 1)
    {
        child = 2 * idx + 1;

        if (child < (free - 1) && highPri(heap[child + 1], heap[child]))
            child++;
        if (highPri(heap[idx], heap[child]))
            break;
        exch(position[heap[idx]], position[heap[child]]);
        exch(heap[idx], heap[child]);
        idx = child;
    }
}

/**
 * @brief pop an array from the heap
 * @param heap array containing the heap
 * @param dist priority of the heap
 * @param free pointer to the int containing the position of where the free is
 * @return int that was poped fromt he list
 */
int HEAP_pop(int heap[], int position[], int dist[], int *free)
{
    int t;
    exch(position[heap[0]], position[heap[(*free) - 1]]);
    position[heap[0]] = -1;
    exch(heap[0], heap[(*free) - 1]);
    FixDown((*free) - 1, heap, position, 0, dist);
    return heap[--(*free)];
}

/**
 * @brief returns the heap position of an array 
 * @param position array containing the position of the verticies
 * @param v vertice to be tested 
 * @return position of the heap 
 */
int get_pos(int position[], int v)
{
    return position[v];
}
