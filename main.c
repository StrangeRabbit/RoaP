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
    int row, column, i1, j1, i2, j2, wall_number;
    mode game_mode;
    FILE *fp;
    char *filename; 
    char output_filename[MAX];
    filename = get_filename(argc, argv);
    fp = open_file(filename);
    get_header(fp, &row, &column, &game_mode, &i1, &j1, &i2, &j2, &wall_number);
    cell *matrix = build_board(fp, row, column, wall_number);
    fclose(fp);
    create_filename(argc, argv, output_filename);
    fp = create_file(output_filename);
    switch (game_mode)
    {
    case A1:
        mode_A1(fp, matrix, i1, j1, row, column);
        break;
    case A2:
        mode_A2(fp, matrix, i1, j1, row, column);
        break;
    case A3:
        mode_A3(fp, matrix, i1, j1, row, column);
        break;
    case A4:
        mode_A4(fp, matrix, i1, j1, row, column);
        break;
    case A5:
        mode_A5(fp, matrix, i1, j1, row, column);
        break;
    case A6:
        mode_A6(fp, matrix, i1, j1, i2, j2, row, column);
        break;
    default:
        exit(INVALID_GAME_MODE);
        break;
    }
    fclose(fp);
    //print_matrix(matrix, row, column);
}

void print_matrix(cell *matrix, int row, int column)
{
    int p;
    for(p = 0; p < row * column; p++){
        printf("%3d", matrix[p].wall);
        if(p % column == column - 1 && p != 0) printf("\n");
    }
}