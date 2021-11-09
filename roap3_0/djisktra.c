#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "djisktra.h"
#include "input.h"
#include "game_mode.h"
#include "heap.h"

int connect_2v(int *dist, int *parent, bool *sptSet, int *graph, int v1, int v2, int C, int L)
{
    int aux = v2 + v2 - v1;
    int flag = 0;
    int i1 = i_idx(v1, C), j1 = j_idx(v1, C), i2 = i_idx(v2, C), j2 = j_idx(v2, C), i_aux = i_idx(aux, C), j_aux = j_idx(aux, C);
    if((graph[v2] == 0) && (dist[v2] > dist[v1]) && (sptSet[v2] == false)){
        
        if(!(i1 != i2 && j1 != j2)){
            parent[v2] = v1;
            if(dist[v2] == INT_MAX) flag = 1;
            else flag = 2;
            dist[v2] = dist[v1];
        }
    }
    if(is_cell_in_board(L, C, i_aux, j_aux)){
        if((graph[v2] > 0) && (graph[aux] == 0) && (dist[aux] > dist[v1] + graph[v2]) && (sptSet[aux] == false)){
            if(!(i1 != i_aux && j1 != j_aux)){
                parent[aux] = v1;
                if(dist[aux] == INT_MAX) flag = 1;
                else flag = 2;
                dist[aux] = dist[v1] + graph[v2];
            }
        }
    }
    return flag;
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

void djisktra(int **graph, int room1, int room2, int* dist, int *parent, bool *sptSet, int V)
{
    int V;
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

    
    
    while(lfree > 0){
        /*
        for(int w = 0; w < lfree; w++)
        {
            printf("%d(%d) - ", heap[w], dist[heap[w]]);
        }
        printf("\n");
        */
        u = pop(heap, dist, &lfree);
        /*
        //printf("u: %d\n", u);
        for(int w = 0; w < lfree; w++)
        {
            printf("%d(%d) - ", heap[w], dist[heap[w]]);
        }
        printf("\n");
        */
        i = i_idx(u, C);
        j = j_idx(u, C);
        //printf("%d %d\n\n\n", i, j);
        sptSet[u] = true;

        if(u == src) break;

        if(is_cell_in_board(L, C, i, j - 1)){
            idx = get_index(C, i, j - 1);
            connected = connect_2v(dist, parent, sptSet, graph, u, idx, C, L);
            //printf("\n\n1 -- %d -- %d\n %d -- %d\n\n\n", idx, dist[idx], idx - 1, dist[idx - 1]);
            if(connected == 1){
                if(graph[idx] != 0) idx--;
                push(idx, dist, heap, hsize, &lfree);
            }
            else if(connected == 2){
                if(graph[idx] != 0) idx--;
                pos = get_pos(heap, idx, lfree);
                //printf("%d\n%d -- %d\n\n", idx, pos, dist[pos]);
                FixUp(heap, pos, dist);
            }
        }
        if(is_cell_in_board(L, C, i, j + 1)){
            idx = get_index(C, i, j + 1);
            connected = connect_2v(dist, parent, sptSet, graph, u, idx, C, L);
            //printf("2 -- %d -- %d\n %d -- %d\n\n\n", idx, dist[idx], idx + 1, dist[idx + 1]);
            if(connected == 1){
                if(graph[idx] != 0) idx++;
                push(idx, dist, heap, hsize, &lfree);
            }
            else if(connected == 2){
                if(graph[idx] != 0) idx++;
                pos = get_pos(heap, idx, lfree);
                //printf("%d\n%d -- %d\n\n", idx, pos, dist[pos]);
                FixUp(heap, pos, dist);
            }
        }
        if(is_cell_in_board(L, C, i - 1, j)){
            idx = get_index(C, i - 1, j);
            connected = connect_2v(dist, parent, sptSet, graph, u, idx, C, L);
            //printf("3 -- %d -- %d\n %d -- %d\n\n\n", idx, dist[idx], idx - C, dist[idx - C]);
            if(connected == 1){
                if(graph[idx] != 0) idx -= C;
                push(idx, dist, heap, hsize, &lfree);
            }
            else if(connected == 2){
                if(graph[idx] != 0) idx -= C;
                pos = get_pos(heap, idx, lfree);
                //printf("%d\n%d -- %d\n\n", idx, pos, dist[pos]);
                FixUp(heap, pos, dist);
            }
        }
        if(is_cell_in_board(L, C, i + 1, j)){
            idx = get_index(C, i + 1, j);
            connected = connect_2v(dist, parent, sptSet, graph, u, idx, C, L);
            //printf("4 -- %d -- %d\n %d -- %d\n\n\n", idx, dist[idx], idx + C, dist[idx + C]);
            if(connected == 1){
                if(graph[idx] != 0) idx += C;
                push(idx, dist, heap, hsize, &lfree);
            }
            else if(connected == 2){
                if(graph[idx] != 0) idx += C;
                pos = get_pos(heap, idx, lfree);
                //printf("%d\n%d -- %d\n\n", idx, pos, dist[pos]);
                FixUp(heap, pos, dist);
            }
        }
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
