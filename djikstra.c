#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "djikstra.h"
#include "heap.h"

/**
 * @brief update distances of all elements connected to the room
 * 
 * @param dist array of distances of the room
 * @param parent array with parents of each room in the shortest path
 * @param sptSet array of tree elements
 * @param graph adjacency list of the graph
 * @param room room to update
 * @param heap heap
 * @param position array of positions of the vertices in the heap
 * @param hsize size of the heap
 * @param lfree first element free in the heap
 */
void connect(int *dist, int *parent, bool *sptSet, _room **graph, int room, int *heap, int *position, int hsize, int *lfree)
{
    _room *aux;
    int flag, pos;
    /* init aux to first position of the list of the vertice */
    aux = graph[room];
    /* update all vertices of the list */
    while (aux != NULL)
    {
        /* flag says if the vertice was added (-1) , updated (2) or nothing (1) to the heap */
        flag = -1;
        /* check if the vertice is already in the heap */
        if (dist[aux->room] != INT_MAX)
            flag = 1;
        /* if vertice has not the shortest path update it */
        if (sptSet[aux->room] == false && (dist[room] + aux->cost < dist[aux->room]))
        {
            parent[aux->room] = room;
            dist[aux->room] = dist[room] + aux->cost;
            if (flag == 1)
                flag = 2;
        }
        /* if vertice isnt in the heap, add it */
        if (flag == -1)
            HEAP_push(aux->room, dist, heap, hsize, lfree, position);
        /* if dist of vertice has been updated, fix it up in the heap */
        else if (flag == 2)
        {
            pos = get_pos(position, aux->room);
            FixUp(heap, position, pos, dist);
        }
        /* go next vertice of the list */
        aux = aux->next;
    }
}

/**
 * @brief shortest path algorithm
 * 
 * @param graph adjacency list of the graph
 * @param room2 the objective
 * @param dist array of distances of the rooms to the source
 * @param parent array of the parents of each room in shortest path
 * @param sptSet array of the elements in the tree
 * @param V number of rooms of the graph
 */
void djisktra(_room **graph, int room2, int *dist, int *parent, bool *sptSet, int V)
{
    unsigned int v;
    int u;
    int *heap;
    int *position;
    int hsize, lfree;
    hinit(V, &heap, &hsize, &lfree, &position);

    for (v = 0; v < V; v++)
    {
        dist[v] = INT_MAX;
        sptSet[v] = false;
    }
    dist[0] = 0;
    sptSet[0] = true;
    parent[0] = 0;
    /* connect the paths of vertice 0 */
    connect(dist, parent, sptSet, graph, 0, heap, position, hsize, &lfree);
    /* while heap isnt empty */
    while (lfree > 0)
    {
        /* pop the shortest path */
        u = HEAP_pop(heap, position, dist, &lfree);
        
        /* put it in the tree */
        sptSet[u] = true;

        /* if we reach the treasure, break */
        if (u == room2)
            break;

        /* connect or update next vertices */
        connect(dist, parent, sptSet, graph, u, heap, position, hsize, &lfree);
        
    }
    /* free heap */
    free(heap);
    free(position);
    return;
}
