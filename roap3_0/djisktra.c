#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "djisktra.h"
#include "input.h"
#include "game_mode.h"
//#include "LinkedList.h"

void connect_2v(int *dist, int *parent, bool *sptSet, int *graph, int v1, int v2, int C)
{
    int aux = v2 + v2 - v1;
    int i1 = i_idx(v1, C), j1 = j_idx(v1, C), i2 = i_idx(v2, C), j2 = j_idx(v2, C), i_aux = i_idx(aux, C), j_aux = j_idx(aux, C);
    if(graph[v2] == 0 && dist[v2] > dist[v1] && sptSet[v2] == false){
        
        if(!(i1 != i2 && j1 != j2)){
            parent[v2] = v1;
            dist[v2] = dist[v1];
        }
    }
    if(graph[v2] > 0 && graph[aux] == 0 && dist[aux] > dist[v1] + graph[v2] && sptSet[aux] == false){
        if(!(i1 != i_aux && j1 != j_aux)){
            parent[aux] = v1;
            dist[aux] = dist[v1] + graph[v2];
        }
    }
    
}

int minDistance(int V, int *dist, bool *sptSet)
{
    int min = INT_MAX, min_index = -1;
    unsigned int v;

    for(v = 0; v < V; v++){
        if(sptSet[v] == false && dist[v] < min){
            min = dist[v]; 
            min_index = v;
        }
    }
    
    return min_index;
}

int i_idx(int idx, int C)
{
    return idx / C;
}

int j_idx(int idx, int C)
{
    return idx % C;
}
/*
typedef struct _vertice
{
    int v;
    int dist;
} vertice;

int  compareItems(Item it1, Item it2)
{
    int i1, i2;

    i1 = ((vertice*)it1)->dist;
    i2 = ((vertice*)it2)->dist;

    if (i1 < i2)
        return -1;
    if (i1 > i2)
        return 1;
    return 0;
}

LinkedList *Push(LinkedList *head, int v, int *dist)
{
    int * err = NULL;
    vertice *V = (int*) malloc(sizeof(vertice));
    V->v = v;
    V->dist = dist[v];
    head = insertSortedLinkedList(head, (Item) v, compareItems, err);
    return head;
}

int Pop(LinkedList **head)
{
    LinkedList *aux = (*head);
    vertice *vert = getItemLinkedList(*head);
    int v = vert->v;
    (*head) = getNextNodeLinkedList(*head);
    free(vert);
    free(aux);
    return v;
}
*/
int *djisktra(int *graph, int L, int C, int* dist, int *parent, bool *sptSet, int src)
{
    int V = L * C;
    unsigned int i, j, v;
    int u;
    //LinkedList *Q = initLinkedList();
    
    for(v = 0; v < V; v++){
        dist[v] = INT_MAX;
        sptSet[v] = false;
    }
    dist[0] = 0;
    sptSet[0] = true;
    parent[0] = 0;
    connect_2v(dist, parent, sptSet, graph, 0, C, C);
    connect_2v(dist, parent, sptSet, graph, 0, 1, C);
    
    for(v = 0; v < (V - 1); v++){
        u = minDistance(V, dist, sptSet);
        if(u == -1) break;

        //printf("u: %d\n", u);
        

        i = i_idx(u, C);
        j = j_idx(u, C);
        //printf("%d %d\n\n\n", i, j);
        sptSet[u] = true;

        if(u == src) break;

        if(is_cell_in_board(L, C, i, j - 1)){
            connect_2v(dist, parent, sptSet, graph, u, get_index(C, i, j - 1), C);
        }
        if(is_cell_in_board(L, C, i, j + 1)){
            connect_2v(dist, parent, sptSet, graph, u, get_index(C, i, j + 1), C);
        }
        if(is_cell_in_board(L, C, i - 1, j)){
            connect_2v(dist, parent, sptSet, graph, u, get_index(C, i - 1, j), C);
        }
        if(is_cell_in_board(L, C, i + 1, j)){
            connect_2v(dist, parent, sptSet, graph, u, get_index(C, i + 1, j), C);
        }
        //printf("%d...\n\n\n\n", v);
        
    }
    return dist;
}
