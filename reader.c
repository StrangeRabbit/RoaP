#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "reader.h"
#include "lib.h"
#include "queue.h"
 /**
  * @brief read the header of the file
  * 
  * @param fp pointer to file
  * @param i pointer to i objective of the map
  * @param j pointer to j objective of the map
  * @param P pointer to number of walls
  */
void header(FILE *fp, int *i, int *j, int *P)
{

    if (fscanf(fp, "%d %d", i, j) != 2) exit(0);
    if (fscanf(fp, "%d", P) != 1) exit(0);
    /* adapt coordinates */
    (*i)--;
    (*j)--;
    return;
}

/**
 * @brief read the walls of the file, create graph and wall queue
 * 
 * @param fp pointer to file
 * @param graph pointer to the graph
 * @param P number of walls
 * @param L lines of graph
 * @param C columns of graph
 * @param queue wall queue
 * @param size size of queue
 * @param pusher position to push
 */
void read_file(FILE *fp, int **graph, int P, int L, int C, int *queue[], int size, int *pusher)
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
    *pusher = 0;
    *queue = (int*) malloc(sizeof(int) * P);
    /* save walls */
    for(a = 0; a < V; a++){
        if((*graph)[a] > 0 && breakable(*graph, a, C, L))
            ARRAY_push(pusher, size, *queue, a);
    }

}


