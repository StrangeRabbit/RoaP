#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "output.h"
#include "game_mode.h"
#include "structures.h"
#include "djisktra.h"
#include "adjacencyList.h"

#define MAX 100

typedef struct _w
{
    int i;
    int j;
    int cost;
} w;

int get_i(list *array, int v)
{
    while (array->vertice != v)
    {
        array = array->next;
    }
    return array->i;
}

int get_j(list *array, int v)
{
    while (array->vertice != v)
    {
        array = array->next;
    }
    return array->j;
}

int get_c(list *array, int v)
{
    while (array->vertice != v)
    {
        array = array->next;
    }
    return array->cost;
}

void print_walls(w *walls, FILE *fp, int P)
{
    int i;
    for (i = P - 1; i >= 0; i--)
    {
        fprintf(fp, "%d %d %d\n", walls[i].i + 1, walls[i].j + 1, walls[i].cost);
    }
    return;
}

int count_walls(int *parent, int src)
{
    int wall = 0;
    while (src != 0)
    {
        wall++;
        src = parent[src];
    }
    return wall;
}

w *get_walls(int *parent, int src, int W, list **graph)
{
    w *walls = (w *)malloc(sizeof(w) * W);
    int i = 0;
    for (i = 0; i < W; i++, src = parent[src])
    {
        walls[i].i = get_i(graph[src], parent[src]);
        walls[i].j = get_j(graph[src], parent[src]);
        walls[i].cost = get_c(graph[src], parent[src]);
    }
    return walls;
}

/** 
 * @brief Main function of the program  
 * @param argc arguments count 
 * @param argv argument vector 
 * @return 0 if successful
 */
int main(int argc, char **argv)
{
    int i1 = 0, j1 = 0, i2 = 0, j2 = 0;
    int L, C, V, i, j, P, treasure, W;
    int NumberOfRooms = 0;
    w *walls = NULL;
    mode game_mode;
    _project project = FINAL;
    list **head = NULL;
    FILE *fp;
    FILE *ofp;
    char *filename;
    int min_j, min_i, flag;
    char output_filename[MAX];
    cell *matrix;
    int *graph;
    int *group;
    int *sz;
    if (argc == 3)
    {
        project = INTERMEDIO;
    }

    // Prepares the program to start receving information
    //program_caller_checker(argc, argv);
    filename = get_filename(argc, argv);
    fp = open_file(filename, argc);
    if (project == INTERMEDIO)
        create_filename(argc, argv, output_filename);
    else
        create_filename_final(argc, argv, output_filename);
    ofp = create_file(output_filename);
    //printf("starting: %s   \n", filename);

    // Start to read the map
    while (fscanf(fp, "%d %d", &L, &C) == 2)
    {
        flag = 1;
        if (project == INTERMEDIO)
        {
            get_header(fp, &game_mode, &i1, &j1, &i2, &j2, &P);

            if (is_cell_in_board(L, C, i1, j1) == false)
                flag = -2;
            if (game_mode == A6)
                if (is_cell_in_board(L, C, i2, j2) == false)
                    flag = -2;
            if (flag == -2)
            {
                jump_map(fp, P);
                fprintf(ofp, "%d\n\n", flag);
                continue;
            }

            // Builds the board that will be played
            matrix = build_board(fp, L, C, P);

            // Calls the game mode
            switch (game_mode)
            {
            case A1:
                mode_A1(ofp, matrix, i1, j1, L, C);
                break;
            case A2:
                mode_A2(ofp, matrix, i1, j1, L, C);
                break;
            case A3:
                mode_A3(ofp, matrix, i1, j1, L, C);
                break;
            case A4:
                mode_A4(ofp, matrix, i1, j1, L, C);
                break;
            case A5:
                mode_A5(ofp, matrix, i1, j1, L, C);
                break;
            case A6:
                mode_A6(ofp, matrix, i1, j1, i2, j2, L, C);
                break;
            default:
                exit(0);
                break;
            }
            // Frees the board
            free(matrix);
        }
        else
        {
            get_header_final(fp, &i, &j, &P);
            V = L * C;
            if (is_cell_in_board(L, C, i, j) == false)
            {
                jump_map(fp, P);
                fprintf(ofp, "%d\n\n", -1);
                continue;
            }
            if (treasure_is_adjacent_to_src(i, j))
            {
                jump_map(fp, P);
                fprintf(ofp, "%d\n\n", (0));
                continue;
            }

            graph = build_graph(fp, C, V, P, &min_j, &min_i);
            if (graph[i * C + j] != 0 || graph[0])
            {
                free(graph);
                fprintf(ofp, "-1\n\n");
                continue;
            }

            // Alocate array that will be used in CWQU
            group = (int *)malloc(L * C * sizeof(int));
            sz = (int *)malloc(L * C * sizeof(int));

            if (group == NULL || sz == NULL)
                exit(0);

            group = CWQU2(graph, L, C, group, sz);

            sz = NULL; // No longer need to keep this array since i wont be neeging the size of the array

            if (same_root2(graph, group, 0, 0, i, j, C, L))
            {
                fprintf(ofp, "%d\n", 0); // Estão na mesma sala
                free(group);
                free(sz);
                free(graph);
                continue;
            }

            NumberOfRooms = CRN(graph, L, C, group);

            treasure = group[i * C + j];
            //printf("%d\n", group[treasure]);
            head = toSmallerMap(NumberOfRooms, group, graph, L, C);

            //treasure = get_index(C, i, j);

            int *dist = (int *)malloc(NumberOfRooms * sizeof(int));
            if (dist == NULL)
                exit(0);

            int *parent = (int *)malloc(NumberOfRooms * sizeof(int));
            if (parent == NULL)
                exit(0);

            bool *sptSet = (bool *)malloc(NumberOfRooms * sizeof(bool));
            if (sptSet == NULL)
                exit(0);

            djisktra(head, treasure, dist, parent, sptSet, NumberOfRooms);

            //printFullList(head, NumberOfRooms);

            //djisktra(graph, L, C, dist, parent, sptSet, treasure);
            /*
            printf("%d %d\n", i, j);
            printf("treasure - %d\n", treasure);
            for(i1 = 0; i1 < NumberOfRooms; i1++)
                printf("(%d)%d \n", i1, dist[i1] == INT_MAX ? -1 : dist[i1]);
            printf("\n\n");
            */

            switch (dist[treasure])
            {
            case INT_MAX:
                fprintf(ofp, "-1\n\n");
                break;

            case 0:
                fprintf(ofp, "%d\n\n", dist[treasure]);
                break;

            default:
                fprintf(ofp, "%d\n", dist[treasure]);
                W = count_walls(parent, treasure);
                fprintf(ofp, "%d\n", W);
                walls = get_walls(parent, treasure, W, head);
                print_walls(walls, ofp, W);
                fprintf(ofp, "\n");
                break;
            }
            if (walls != NULL)
            {
                free(walls);
                walls = NULL;
            }
            free(dist);
            free(parent);
            free(sptSet);
            freeMatrix(head, NumberOfRooms);

            dist = parent = NULL;
            sptSet = NULL;
            head = NULL;
        }
    }

    // Closes all the files
    fclose(ofp);
    fclose(fp);

    exit(0);
}
