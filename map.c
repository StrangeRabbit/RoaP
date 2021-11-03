#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define abort() printf("GOT FUCKED\n");
#define newline() fprintf(output, "\n");

int main(int argc, char **argv)
{
    int L, C, P, i, j, v;
    char shit[5];
    FILE *fp = fopen(argv[1], "r");
    FILE *output = fopen("map.txt", "w");
    fscanf(fp, "%d %d", &L, &C);
    fscanf(fp, "%d %d" , &i, &j);
    fscanf(fp, "%d", &P);
    int **graph = (int**) calloc(L, sizeof(int*));
    if(graph == NULL) {abort(); exit(0);} 
    for(int a = 0; a < L; a++){
        graph[a] = (int*) calloc(C, sizeof(int));
        if(graph[a] == NULL) {abort(); exit(0);} 
    }
    for(int a = 0; a < P; a++)
    {
        fscanf(fp, "%d %d %d", &i, &j, &v);
        graph[i][j] = v;
    }
    for(int a  = 0; a < L; a++)
    {
        for(int b = 0; b < C; b++)
        {
            fprintf(output, "%6d ", graph[a][b]);
        }
        newline();
        free(graph[a]);
    }
    free(graph);
    fclose(fp);
    fclose(output);
}