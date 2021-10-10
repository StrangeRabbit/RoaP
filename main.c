#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "output.h"
#include "game_mode.h"
#include "structures.h"

#define MAX 100

void print_matrix(cell *matrix, int row, int column);

int main(int argc, char** argv)
{
    int row, column, i1 = 0, j1 = 0, i2 = 0, j2 = 0, wall_number;
    mode game_mode;
    FILE *fp;
    FILE *ofp;
    char *filename; 
    char output_filename[MAX];
    cell *matrix;
    program_caller_checker(argc, argv);
    filename = get_filename(argc, argv);
    fp = open_file(filename);
    create_filename(argc, argv, output_filename);
    ofp = create_file(output_filename);
    while (fscanf(fp, "%d %d", &row, &column) == 2){
        get_header(fp, &game_mode, &i1, &j1, &i2, &j2, &wall_number);
        matrix = build_board(fp, row, column, wall_number);
        //print_matrix(matrix, row, column);
        //printf("row: %d\ncolumn: %d\ngame mode: %d\ni1: %d\nj1: %d\ni2: %d\nj2: %d\nwall number: %d\n\n\n", row, column, game_mode, i1, j1, i2, j2, wall_number);
        switch (game_mode)
        {
        case A1:
            mode_A1(ofp, matrix, i1, j1, row, column);
            break;
        case A2:
            mode_A2(ofp, matrix, i1, j1, row, column);
            break;
        case A3:
            mode_A3(ofp, matrix, i1, j1, row, column);
            break;
        case A4:
            mode_A4(ofp, matrix, i1, j1, row, column);
            break;
        case A5:
            mode_A5(ofp, matrix, i1, j1, row, column);
            break;
        case A6:
            mode_A6(ofp, matrix, i1, j1, i2, j2, row, column);
            break;
        default:
            exit(0);
            break;
        }
        free(matrix);
    }
    fclose(ofp);
    fclose(fp);
    exit(0);
}

void print_matrix(cell *matrix, int row, int column)
{
    int p;
    for(p = 0; p < row * column; p++){
        printf("%3d", matrix[p].wall);
        if(p % column == column - 1 && p != 0) printf("\n");
    }
    printf("\n\n\n");
}