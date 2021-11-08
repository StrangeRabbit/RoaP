#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "output.h"
#include "game_mode.h"
#include "structures.h"
#include "djisktra.h"

#define MAX 100


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
    int *walls;
    mode game_mode;
    _project project = FINAL;
    FILE *fp;
    FILE *ofp;
    char *filename;
    int flag;
    char output_filename[MAX];
    cell *matrix;
    int *graph;
    unsigned long position = 0;
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
            if (is_cell_in_board(L, C, i, j) == false){
                jump_map(fp, P);
                fprintf(ofp, "%d\n\n", -1);
                continue;
            }
            if (treasure_is_adjacent_to_src(i, j)){
                jump_map(fp, P);
                fprintf(ofp, "%d\n\n", 0);
                continue;
            }

            
            position = ftell(fp);
            /*
            flag = check(fp, P, i, j);
            printf("%d\n", flag);
            if(flag == 1)
                fseek(fp, position, SEEK_SET);
            else 
            {
                fprintf(ofp, "%d\n\n", flag);
                continue;
            }
            */
            graph = build_graph(fp, C, V, P);
            /*
            for(i1 = 0; i1 < V; i1++)
            {
                if(i1 % C == 0) printf("\n");
                printf("(%2d)%3d ", i1, graph[i1]);
            }
            printf("\n\n\n");
            */
            int *dist = (int *)malloc(V * sizeof(int));
            if (dist == NULL)
                exit(0);

            int *parent = (int *)malloc(V * sizeof(int));
            if (parent == NULL)
                exit(0);

            bool *sptSet = (bool *)malloc(V * sizeof(bool));
            if (sptSet == NULL)
                exit(0);
            treasure = get_index(C, i, j);

            djisktra(graph, L, C, dist, parent, sptSet, treasure);

            /*
            printf("%d %d\n", i, j);
            printf("treasure - %d\n", treasure);
            for(i1 = 0; i1 < V; i1++)
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
                W = count_walls(parent, treasure, C);
                fprintf(ofp, "%d\n", W);
                walls = get_walls(parent, treasure, W, C);
                print_walls(W, treasure, walls, graph, ofp, C);
                fprintf(ofp, "\n");
                break;
            }

            free(graph);
            free(dist);
            free(parent);
            free(sptSet);
        }
    }

    // Closes all the files
    fclose(ofp);
    fclose(fp);

    exit(0);
}
