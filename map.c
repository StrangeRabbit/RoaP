#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define abort() printf("GOT FUCKED\n");
#define newline() fprintf(output, "\n");

void print_walls(int V, int C, int *dist, int *parent, int *graph, int walls, FILE *fp)
{
    int aux = parent[V] - V;
    int v = V + aux / 2;
    int caller = aux != 1 && aux != -1 && aux != C && aux != -C;
    if(parent[V] != 0) {
        if (caller){
            print_walls(parent[V], C, dist, parent, graph, ++walls, fp);
        }
        else{
            print_walls(parent[V], C, dist, parent, graph, walls, fp);
        }
        
    }
    if(parent[V] == 0 && V != 1 && V != C) walls++;
    if(parent[V] == 0)
        fprintf(fp, "%d\n", walls);
    if(caller){
        fprintf(fp, "%d %d %d\n", i_idx(v, C) + 1, j_idx(v, C) + 1, graph[v]);
        //fprintf(fp, "%d %d %d -- %d\n", V, v, parent[V], aux);
        
    }
    return;
}

void print_walls(int P, int src, int *walls, int *graph, FILE *fp, int C)
{
    int i;
    for(i = P - 1; i >= 0; i--){
        fprintf(fp, "%d %d %d\n", i_idx(walls[i], C) + 1, j_idx(walls[i], C) + 1, graph[walls[i]]);
    }
    return;
}

int count_walls(int *parent, int src, int C)
{
    int aux, wall = 0;
    while(src != 0){
        aux = parent[src] - src;
        if(aux != 1 && aux != -1 && aux != C && aux != -C)
            wall++;
        src = parent[src];
    }
    return wall;
}

int *get_walls(int *parent, int src, int W, int C)
{
    int *walls = (int*) malloc(sizeof(int) * W);
    int aux, wall = 0;
    int i = 0;
    while(src != 0){
        aux = parent[src] - src;
        if(aux != 1 && aux != -1 && aux != C && aux != -C){
            wall = src + aux / 2;
            walls[i] = wall;
            i++;
        }
        src = parent[src];
    }
    return walls;
}
