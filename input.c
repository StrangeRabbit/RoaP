#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

char *get_filename(int argc, char **argv)
{
    if(argc == 2) return argv[1];
    else if(argc == 3) return argv[2];
    else exit(FILE_NAME_ERROR);
}

FILE *open_file(char *filename)
{
    if(file_checker(filename) == FALSE)
        exit(FILE_NAME_ERROR);
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
        exit(FILE_NAME_ERROR);
    return fp;
}

BOOL file_checker(char *filename)
{
    int len = strlen(filename);

    if(strcmp(&filename[len - 4], ".in1") == 0)
        return TRUE;
    else
        return FALSE;
}

void get_header(FILE *fp, int *row, int* column, mode *game_mode, int *i1, int *j1, int *i2, int *j2, int *wall_number)
{
    char mode_aux[3];

    if(fscanf(fp, "%d %d", row, column) != 2) exit(READ_FILE_ERROR);
    if(fscanf(fp, "%d %d", i1, j1) != 2) exit(READ_FILE_ERROR);
    if(fscanf(fp, "%s", mode_aux) != 1) exit(READ_FILE_ERROR);
    (*game_mode) = atoi(&mode_aux[1]);
    if((*game_mode) == A6)
        if(fscanf(fp, "%d %d", i2, j2) != 2) exit(READ_FILE_ERROR);
    if(fscanf(fp, "%d", wall_number) != 1) exit(READ_FILE_ERROR);
    return;
}

cell *build_board(FILE *fp, int row, int column, int wall_number)
{
    unsigned int p;
    int i, j, wall;

    cell *matrix = init_matrix(row, column);
    for(p = 0; p < wall_number; p++){
        fscanf(fp, "%d %d %d", &i, &j, &wall);
        matrix[get_index(column, i - 1, j - 1)].wall = wall;
    }
    return matrix;
}

cell *init_matrix(int row, int column)
{
    unsigned int i;
    
    cell *matrix = (cell*) malloc(row * column * sizeof(cell)); 

    for (i = 0; i < row * column; i++)
    {
        matrix[i].group = i;
        matrix[i].wall = 0;
        matrix[i].sz = 1;
    }
    return matrix;
}

int get_index(int column, int i, int j)
{
    return i * column + j;
}
