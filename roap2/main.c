#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "defs.h"
#include "LinkedList.h"

typedef struct _vertice {unsigned int v; int cost;} vertice;


LinkedList **initArray(int L, int C)
{
    unsigned int i, V = L * C;
    /* allocate array of lists */
    LinkedList **array = (LinkedList**) malloc(V * sizeof(vertice*));
    /* init lists */
    for(i = 0; i < V; i++)
    {
        array[i] = initLinkedList();
    }
    return array;
}

int in_board(int L, int C, int i, int j)
{
    if (i > L - 1 || i < 0 || j > C - 1 || j < 0)
        return 0;
    else
        return 1;
}

int get_index(int C, int i, int j)
{
    return C * i + j;
}

int white(int**matrix, int i, int j)
{
    if(matrix[i][j] == 0) return 1;
    else return 0;
}

int grey(int**matrix, int i, int j)
{
    if(matrix[i][j] > 0) return 1;
    else return 0;
}

int black(int**matrix, int i, int j)
{
    if(matrix[i][j] == -1) return 1;
    else return 0;
}

int  compareItems(Item it1, Item it2)
{
    int i1, i2;

    i1 = ((vertice*)it1)->cost;
    i2 = ((vertice*)it2)->cost;

    if (i1 < i2)
        return -1;
    if (i1 > i2)
        return 1;
    return 0;
}

void uniGraph(LinkedList **array, int** matrix, int L, int C)
{
    int *err = NULL;
    int i, j, p;
    int xx, yy;
    int index1, index2;
    int x[] = {1, 0}, y[] = {0, 1};
    vertice* aux;
    /* go thought all vertices */
    for(i = 0; i < L; i++){
        for(j = 0; j < C; j++){
            /* just try to connect if white */
            if(white(matrix, i, j) == 0) continue;
            /* try to connect the right and down vertices */
            for(p = 0; p < 2; p++){
                /* pass out of board and black vertices */
                if(in_board(L, C, i + y[p], j + x[p]) == 0) continue;
                if(black(matrix, i, j)) continue;
                /* for default this is a white vertice */
                xx = 0;
                yy = 0;
                /* if not white, we unit the piece after */
                if(grey(matrix, i + y[p], j + x[p])){
                    if(y[p] == 1){
                        yy = 1;
                    }
                    else{
                        xx = 1;
                    }
                }
                if(matrix[i + y[p] + yy][j + x[p] + xx] != 0) continue;
                index1 = get_index(C, i + y[p] + yy, j + x[p] + xx);
                index2 = get_index(C, i, j);
                /* create the vertices to put in the lists and insert them */
                aux = (vertice*) malloc(sizeof(vertice));

                aux->cost = matrix[i + y[p]][j + x[p]];
                aux->v = index1;
                
                array[index2] = insertSortedLinkedList(array[index2], aux, compareItems, err);
                
                aux = (vertice*) malloc(sizeof(vertice));
                
                aux->cost = matrix[i + y[p]][j + x[p]];
                aux->v = index2;
                
                array[index1] = insertSortedLinkedList(array[index1], aux, compareItems, err);
                
            }
        }
    }
}


int check_filename(char *filename)
{
    int len = strlen(filename);

    /* check extension of the file */
    if(strcmp(&filename[len - 3], ".in") == 0) return 1;
    return 0;
}

void get_header(FILE *fp, int *i, int *j, int *P)
{
    /* read treasure cell */
    if (fscanf(fp, "%d %d", i, j) != 2) exit(0);
    /* read number of walls */
    if (fscanf(fp, "%d", P) != 1) exit(0);
    /* adapt i and j to board representation */
    (*i)--;
    (*j)--;
    return;
}

int** build_matrix(FILE* fp, int L, int C, int P)
{
    int p, i, j, v;
    /* allocate matrix of 2 dimensions */
    int **matrix = (int**) malloc(L * sizeof(int*));
    if(matrix == NULL) exit(0);
    for(i = 0; i < L; i++){
        matrix[i] = (int*) calloc(C, sizeof(int));
        if(matrix[i] == NULL) exit(0);
    }
    /* get values for walls */
    for(p = 0; p < P; p++)
    {
        if(fscanf(fp, "%d %d %d", &i, &j, &v) != 3) exit(0);
        matrix[--i][--j] = v;
    }
    return matrix;
}

bool breakable(int **graph, int i, int j, int i_src, int j_src, int L, int C)
{
    int i_aux = i - i_src;
    int j_aux = j - j_src;
    if (in_board(L, C,i + i_aux,j + j_aux) == 0) 
        return false;
    
    if(graph[i + i_aux][j + j_aux] == 0)
        return true;
    else
        return false;
}


int minDistance(int dist[], int sptSet[], int V)
{
    int min = INT_MAX, min_index;
    for(int v = 0; v < V; v++){
        if(sptSet[v] == false && dist[v] <= min){
            min = dist[v]; min_index = v;
        }
    }
    return min_index;
}



void dijkstra(int **graph, int src, int L, int C)
{
    int V = L * C, idx;
    int *dist = (int*) malloc(V * sizeof(int));
    int *org = (int*) malloc(V * sizeof(int));
    bool *sptSet = (bool*) malloc(V * sizeof(bool));
    for(int i = 0; i < V; i++){
        dist[i] = INT_MAX;
        org[i] = -1;
        sptSet[i] = false;
    }
    int latest_added_i;
    int latest_added_j;
    dist[src] = 0;
    org[src] = src;
    sptSet[src] = true;
    
           

}

int idx_i(idx, C)
{
    return idx / C;
}

int idx_j(idx, C)
{
    return idx % C;
}

int main(int argc, char **argv)
{
    int L, C, i, j, P;
    int **matrix;
    FILE *fp, *f1, *f2;
    vertice *aux;
    LinkedList **array, *aux1;
    char *filename = argv[1];
    if(check_filename(filename) == 0) exit(0);
    /* open read file */
    fp = fopen(filename, "r");
    /* read all maps */
    while(fscanf(fp, "%d %d", &L, &C) == 2){
        get_header(fp, &i, &j, &P);
        matrix = build_matrix(fp, L, C, P);
        array = initArray(L, C);
        uniGraph(array, matrix, L, C);
        f1 = fopen("map", "w");
        f2 = fopen("test", "w");
        for(i = 0; i < L; i++){
            for (j = 0; j < C; j++){
                fprintf(f1, "%6d", matrix[i][j]);
            }
            fprintf(f1, "\n");
        }

        for(i = 0; i < L * C; i++){
            aux1 = array[i];
            while(aux1 != NULL){
                aux = getItemLinkedList(aux1);
                fprintf(f2, "%6d -- ", aux->cost);
                aux1 = getNextNodeLinkedList(aux1);
            }
            fprintf(f2, "    -1\n");
        }
    }
}
