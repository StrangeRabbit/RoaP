#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "structures.h"

void print_matrix(cell *matrix, int row, int column);

int main(int argc, char** argv)
{
    int row, column, i1, j1, i2, j2, wall_number;
    mode game_mode;
    FILE *fp;
    char *filename; 
    filename = get_filename(argc, argv);
    fp = open_file(filename);
    get_header(fp, &row, &column, &game_mode, &i1, &j1, &i2, &j2, &wall_number);
    cell *matrix = build_board(fp, row, column, wall_number);
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