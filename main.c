#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "bfs.h"
#include "djikstra.h"
#include "lib.h"
#include "list.h"
#include "queue.h"
#include "reader.h"

#define MAX_LENGHT 100

int main(int argc, char **argv)
{
    //unsigned int a;
    //edge *aux;
    //_room *aux;
    
    int i, j, P, *graph, L, C, N_rooms, objective, final_room, *dist, *parent;
    bool *sptSet;
    FILE *fp, *ofp;
    edge *head = NULL, *tail = NULL;
    _room **list;
    char *filename = argv[1], ofn[MAX_LENGHT];
    
    /* check program invocation */
    if(argc != 2) exit(0);

    /* check filename */
    if(strcmp(&filename[strlen(filename) - 3], ".in") != 0) exit(0);

    /* open read file */
    fp = fopen(filename, "r");
    if(fp == NULL) exit(0);

    /* generate output file name */
    strcpy(ofn, filename);
    strcpy(&ofn[strlen(ofn) - 2], "sol");

    /* open output file */
    ofp = fopen(ofn, "w");
    if(ofp == NULL) exit(0);

    while(fscanf(fp, "%d %d", &L, &C) == 2){

        /* get  header */
        header(fp, &i, &j, &P);

        /* check objective point */
        if(i < 0 || i > L - 1 || j < 0 || j > C - 1){
            fprintf(ofp, "-1\n\n");
            jump_map(fp, P);
            continue;
        }

        /* read file, save graph and save walls */
        objective = idx(i, j, C);
        read_file(fp, &graph, filename, P, L, C, &head, &tail);

        /* validate input data */
        if(!white(0, graph) || !white(objective, graph)){
            fprintf(ofp, "-1\n\n");
            free(graph);
            continue;
        }
        
        /* connect rooms */
        bfs(graph, L, C, &N_rooms);

        /* check cost 0 */
        if(graph[0] == graph[objective])
        {
            fprintf(ofp, "0\n\n");
            free(graph);
            continue;
        }
        
        /* get room of the treasure */
        final_room = graph[objective] * (-1) - 2;
        
        /* build list */
        list = create_list(graph, N_rooms, head, tail, L, C);
        
        /* free matrix */
        free(graph);

        /* ready to djikstra */
        dist = (int*) malloc(N_rooms * sizeof(int));
        if(dist == NULL) exit(0);

        parent = (int*) malloc(N_rooms * sizeof(int));
        if(parent == NULL) exit(0);

        sptSet = (bool*) malloc(N_rooms * sizeof(bool));
        if(sptSet == NULL) exit(0);

        /* get shortest path */
        djisktra(list, final_room, dist, parent, sptSet, N_rooms);

        fprintf(ofp, "%d\n\n", dist[final_room]);

        /* free stuff */
        free(dist);
        free(parent);
        free(sptSet);
        free_list(list, N_rooms);
        
    }
    /* close files */
    fclose(fp);
    fclose(ofp);
}
