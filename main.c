#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include "bfs.h"
#include "djikstra.h"
#include "lib.h"
#include "list.h"
#include "queue.h"
#include "reader.h"
#include "print.h"

#include <time.h>

#define MAX_LENGHT 100

int main(int argc, char **argv)
{
    //unsigned int a;
    //edge *aux;
    //_room *aux;
    clock_t begin, end;
    int i, j, P, *graph, L, C, N_rooms, objective, final_room, *dist, *parent;
    bool *sptSet;
    FILE *fp, *ofp;
    edge *head = NULL, *tail = NULL;
    _room **list;
    char *filename = argv[1], ofn[MAX_LENGHT];

    /* check program invocation */
    if (argc != 2)
        exit(0);

    /* check filename */
    if (strcmp(&filename[strlen(filename) - 3], ".in") != 0)
        exit(0);

    /* open read file */
    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(0);

    /* generate output file name */
    strcpy(ofn, filename);
    strcpy(&ofn[strlen(ofn) - 2], "sol");

    /* open output file */
    ofp = fopen(ofn, "w");
    if (ofp == NULL)
        exit(0);

    while (fscanf(fp, "%d %d", &L, &C) == 2)
    {

        /* get  header */
        header(fp, &i, &j, &P);

        /* check objective point */
        if (i < 0 || i > L - 1 || j < 0 || j > C - 1)
        {
            fprintf(ofp, "-1\n\n");
            jump_map(fp, P);
            continue;
        }
        if((i == 1 && j == 0) || (i == 0 && j == 1)){
            fprintf(ofp, "0\n\n");
            jump_map(fp, P);
            continue;
        }
        begin = clock();
        /* read file, save graph and save walls */
        objective = idx(i, j, C);
        read_file(fp, &graph, filename, P, L, C, &head, &tail);
        end = clock();
        printf("time of read: %f\n", (double) (end - begin) / CLOCKS_PER_SEC);
        /* validate input data */
        if (!white(0, graph) || !white(objective, graph))
        {
            fprintf(ofp, "-1\n\n");
            free(graph);
            BFS_empty_queue(&head, &tail);
            continue;
        }
        begin = clock();
        /* connect rooms */
        bfs(graph, L, C, &N_rooms);
        end = clock();
        printf("time of bfs: %f\n", (double) (end - begin) / CLOCKS_PER_SEC);
        /* check cost 0 */
        if (graph[0] == graph[objective])
        {
            fprintf(ofp, "0\n\n");
            free(graph);
            BFS_empty_queue(&head, &tail);
            continue;
        }

        /* get room of the treasure */
        final_room = graph[objective] * (-1) - 2;
        begin = clock();
        /* build list */
        list = create_list(graph, N_rooms, head, tail, L, C);
        end = clock();
        printf("time of creating list: %f\n", (double) (end - begin) / CLOCKS_PER_SEC);
        /* free matrix */
        free(graph);

        /* ready to djikstra */
        dist = (int *)malloc(N_rooms * sizeof(int));
        if (dist == NULL)
            exit(0);

        parent = (int *)malloc(N_rooms * sizeof(int));
        if (parent == NULL)
            exit(0);

        sptSet = (bool *)malloc(N_rooms * sizeof(bool));
        if (sptSet == NULL)
            exit(0);
        begin = clock();
        /* get shortest path */
        djisktra(list, final_room, dist, parent, sptSet, N_rooms);
        end = clock();
        printf("time of djikstra: %f\n", (double) (end - begin) / CLOCKS_PER_SEC);
        switch (dist[final_room])
        {
        case INT_MAX:
            fprintf(ofp, "%d\n\n", -1);
            break;
        case 0:

            fprintf(ofp, "%d\n\n", 0);
            break;
        default:
            fprintf(ofp, "%d\n", dist[final_room]);
            printWalls(list, parent, final_room, ofp, C, 0);
            fprintf(ofp, "\n");
        }

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
