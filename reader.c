#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "reader.h"
#include "lib.h"

void header(FILE *fp, int *i, int *j, int *P)
{

    if (fscanf(fp, "%d %d", i, j) != 2) exit(0);
    if (fscanf(fp, "%d", P) != 1) exit(0);
    /* adapt coordinates */
    (*i)--;
    (*j)--;
    return;
}

void read_file(FILE *fp, int **graph, char *filename, int P, int L, int C, edge **head, edge **tail)
{
    int i, j, v;
    unsigned int a;
    int V = L * C;

    /* init graph */
    *graph = (int*) malloc(V * sizeof(int));
    for(a = 0; a < V; a++)
        (*graph)[a] = 0;

    /* read and save graph */
    for(a = 0; a < P; a++){
        if(fscanf(fp, "%d %d %d", &i, &j, &v) != 3) exit(0);
        i--; j--;
        (*graph)[idx(i, j, C)] = v;
    }
    *head = NULL; *tail = NULL;
    /* save walls */
    for(a = 0; a < V; a++){
        if((*graph)[a] > 0 && breakable(*graph, a, C, L))
            BFS_push(head, tail, a);
    }

}


