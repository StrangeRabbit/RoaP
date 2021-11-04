#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "output.h"
#include "game_mode.h"
#include "structures.h"

#define MAX 100

/** 
 * @brief Main function of the program  
 * @param argc arguments count 
 * @param argv argument vector 
 * @return 0 if successful
 */
int main(int argc, char **argv)
{
    int i1 = 0, j1 = 0, i2 = 0, j2 = 0;
    int L, C, V, i, j, P;
    mode game_mode;
    _project project = FINAL;
    FILE *fp;
    FILE *ofp;
    char *filename;
    int flag;
    char output_filename[MAX];
    cell *matrix;
    int *graph;
    if(argc == 3){
        project = INTERMEDIO;
    }
    // Prepares the program to start receving information
    //program_caller_checker(argc, argv);
    filename = get_filename(argc, argv);
    fp = open_file(filename, argc);
    if(project == INTERMEDIO)
        create_filename(argc, argv, output_filename);
    else
        create_filename_final(argc, argv, output_filename);
    ofp = create_file(output_filename);

    // Start to read the map
    while (fscanf(fp, "%d %d", &L, &C) == 2)
    {
        flag = 0;
        if(project == INTERMEDIO){
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
        else{
            V = L * C;
            get_header_final(fp, &i, &j, &P);
            if (is_cell_in_board(L, C, i, j) == false)
                flag = -1;
            if(treasure_is_adjacent_to_src(i, j))
                flag = -1;

            if (flag == -1)
            {
                jump_map(fp, P);
                fprintf(ofp, "%d\n\n", flag);
                continue;
            }

            graph = build_graph(fp, C, V, P);
            
            fprintf(ofp, "check\n\n");
            free(graph);
        }
        
    }
    // Closes all the files
    fclose(ofp);
    fclose(fp);

    exit(0);
}
