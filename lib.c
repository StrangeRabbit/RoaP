#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib.h"

bool white(int V, int *graph)
{
    if(graph[V] == 0) return true;
    return false;
}

int I(int idx, int C)
{
    return idx / C;
}

int J(int idx, int C)
{
    return idx % C;
}

int idx(int i, int j, int C)
{
    return i * C + j;
}

bool breakable(int *graph, int v, int C, int L)
{
    if(I(v + 1, C) == I(v - 1, C))
        if(graph[v + 1] == 0 && graph[v - 1] == 0)
            return true;
    
    if(I(v + C, C) < L && I(v - C, C) > -1 && v - C > -1)
        if(graph[v + C] == 0 && graph[v - C] == 0)
            return true;
    return false;
}

bool in_board(int v, int L, int C)
{
    int V = L * C, i = I(v, C);
    if(i < L && i > -1 && v > -1 && v < V) return true;
    else return false;
}

void jump_map(FILE *fp, int P)
{
    int a, i, j, v;
    for(a = 0; a < P; a++)
    {
        if(fscanf(fp, "%d %d %d", &i, &j, &v) != 3) exit(0);
    }
}
