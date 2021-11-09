#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "djisktra.h"
#include "input.h"
#include "game_mode.h"
#include "heap.h"


void connect(int *dist, int *parent, bool *sptSet, list **graph, int room, int *heap, int hsize, int *lfree)
{
    list *aux;
    int flag, pos;
    /* init aux to first position of the list of the vertice */
    aux = graph[room];
    /* update all vertices of the list */
    while(aux != NULL){
        /* flag says if the vertice was added (-1) , updated (2) or nothing (1) to the heap */
        flag = -1;
        /* check if the vertice is already in the heap */
        if(dist[aux->vertice] != INT_MAX)
            flag = 1;
        /* if vertice has not the shortest path update it */
        if(sptSet[aux->vertice] == false && (dist[room] + aux->cost < dist[aux->vertice])){
            parent[aux->vertice] = room;
            dist[aux->vertice] = dist[room] + aux->cost;
            if(flag == 1) flag = 2;
        }
        /* if vertice isnt in the heap, add it */
        if(flag == -1)
            push(aux->vertice, dist, heap, hsize, lfree);
        /* if dist of vertice has been updated, fix it up in the heap */
        else if(flag == 2){
            pos = get_pos(heap, aux->vertice, *lfree);
            FixUp(heap, pos, dist);
        }
        /* go next vertice of the list */
        aux = aux->next;
    }
}

int i_idx(int idx, int C)
{
    return idx / C;
}

int j_idx(int idx, int C)
{
    return idx % C;
}

void djisktra(list **graph, int room2, int* dist, int *parent, bool *sptSet, int V)
{
    unsigned int i, j, v;
    int u;
    int *heap;
    int hsize, lfree;
    int connected, pos, idx;
    hinit(V, &heap, &hsize, &lfree);
    
    for(v = 0; v < V; v++){
        dist[v] = INT_MAX;
        sptSet[v] = false;
    }
    dist[0] = 0;
    sptSet[0] = true;
    parent[0] = 0;
    /* connect the paths of vertice 0 */
    connect(dist, parent, sptSet, graph, 0, heap, hsize, &lfree);
    
    while(lfree > 0){
        /*
        for(int w = 0; w < lfree; w++)
        {
            printf("%d(%d) - ", heap[w], dist[heap[w]]);
        }
        printf("\n");
        */
       /* pop the shortest path */
        u = pop(heap, dist, &lfree);
        /*
        //printf("u: %d\n", u);
        for(int w = 0; w < lfree; w++)
        {
            printf("%d(%d) - ", heap[w], dist[heap[w]]);
        }
        printf("\n");
        */
        //printf("%d %d\n\n\n", i, j);
        /* put it in the tree */
        sptSet[u] = true;
        /* if we reach the treasure, stop */
        if(u == room2) break;
        /* connect or update next vertices */
        connect(dist, parent, sptSet, graph, u, heap, hsize, &lfree);
        /*
        for(int w = 0; w < lfree; w++)
        {
            printf("%d(%d) - ", heap[w], dist[heap[w]]);
        }
        printf("\n\n\n\n");
        */
        /*
        int rand;
        scanf("%d", &rand);
        printf("%d\n", dist[rand]);
        */
    }
    free(heap);
    return;
}
