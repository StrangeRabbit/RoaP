#include <stdio.h>
#include <stdlib.h>

#include "game_mode.h"
#include "input.h"

BOOL is_cell_in_board(int row, int column, int i, int j)
{
    if(i > row || i < 1 || j > column || j < 1)
        return FALSE;
    else
        return TRUE;
}

void mode_A1(FILE *fp, cell *matrix, int i, int j, int row, int column)
{
    int cell_type = -2;
    if(is_cell_in_board(row, column, i, j) == FALSE){
        fprintf(fp, "%d", cell_type);
    }
    else{
        fprintf(fp, "%d", matrix[get_index(column, i, j)].wall);
    }
    return;
}

void mode_A2(FILE *fp, cell *matrix, int i, int j, int row, int column)
{
    unsigned int p;
    int flag = 0;
    int around_x[] = {-1, 0, 1, 0};
    int around_y[] = {0, 1, 0, -1};
    if(is_cell_in_board(row, column, i, j) == FALSE) flag = -2;
    else{
        for(p = 0; p < 4; p++){
            if(is_cell_in_board(row, column, i + around_y[p], j + around_x[p]) == FALSE) continue;
            if(is_white(matrix[get_index(column, i + around_y[p], j + around_y[p])]) == TRUE) flag = 1;
        }
    }
    fprintf(fp, "%d", flag);
    return;
}

void mode_A3(FILE *fp, cell *matrix, int i, int j, int row, int column)
{
    unsigned int p;
    int flag = 0;
    int around_x[] = {-1, 0, 1, 0};
    int around_y[] = {0, 1, 0, -1};
    if(is_cell_in_board(row, column, i, j) == FALSE) flag = -2;
    else{
        for(p = 0; p < 4; p++){
            if(is_cell_in_board(row, column, i + around_y[p], j + around_x[p]) == FALSE) continue;
            if(is_grey(matrix[get_index(column, i + around_y[p], j + around_y[p])]) == TRUE) flag = 1;
        }
    }
    fprintf(fp, "%d", flag);
    return;
}

void mode_A4(FILE *fp, cell *matrix, int i, int j, int row, int column)
{
    unsigned int p;
    int flag = 0;
    int around_x[] = {-1, 0, 1, 0};
    int around_y[] = {0, 1, 0, -1};
    if(is_cell_in_board(row, column, i, j) == FALSE) flag = -2;
    else{
        for(p = 0; p < 4; p++){
            if(is_cell_in_board(row, column, i + around_y[p], j + around_x[p]) == FALSE) continue;
            if(is_black(matrix[get_index(column, i + around_y[p], j + around_y[p])]) == TRUE) flag = 1;
        }
    }
    fprintf(fp, "%d", flag);
    return;
}

void mode_A5(FILE *fp, cell *matrix, int i, int j, int row, int column)
{
    int flag = 0;
    if(is_cell_in_board(row, column, i, j) == FALSE) flag = -2;
    else if(is_grey(matrix[get_index(column, i, j)]) == FALSE) flag = -1;
    else{
        if(is_cell_in_board(row, column, i, j - 1) == TRUE && is_cell_in_board(row, column, i, j + 1) == TRUE)
            if(is_white(matrix[get_index(column, i, j + 1)]) == TRUE && is_white(matrix[get_index(column, i, j - 1)]) == TRUE)
                flag = 1;
        if(is_cell_in_board(row, column, i + 1, j) == TRUE && is_cell_in_board(row, column, i - 1, j) == TRUE)
            if(is_white(matrix[get_index(column, i + 1, j)]) == TRUE && is_white(matrix[get_index(column, i - 1, j)]) == TRUE)
                flag = 1;
    }
    fprintf(fp, "%d", flag);
    return;
}

void mode_A6(FILE *fp, cell *matrix, int i1, int j1, int i2, int j2, int row, int column)
{
    int flag;
    CWQU(matrix, row, column);
    flag = same_root(matrix, row, column, i1, j1, i2, j2);
    fprintf(fp, "%d", flag);
    return;
}

int same_root(cell *matrix, int row, int column, int i1, int j1, int i2, int j2)
{
    int cell1 = get_index(column, i1, j1);
    int cell2 = get_index(column, i2, j2);
    int p, q;
    
    for(p = cell1; p != matrix[p].group; p = matrix[p].group);
    for(q = cell2; q != matrix[q].group; q = matrix[q].group);
    
    if(p == q) return 1;
    else return 0;

}

void CWQU(cell *matrix, int row, int column)
{
    int i, j;
    int cell_index;
    int front_cell_index;
    int under_cell_index;
    int p, q, t, x;
    for(i = 0; i < row; i++){
        for(j = 0; j < column; j++){
            cell_index = get_index(column, i, j);
            if(is_white(matrix[cell_index]) == FALSE) continue;
            if(is_cell_in_board(row, column, i, j + 1) == TRUE && is_white(matrix[get_index(column, i, j + 1)]) == TRUE){
                front_cell_index = get_index(column, i, j + 1);
                
                // do search first
                for(p = cell_index; p != matrix[p].group; p = matrix[p].group);
                for(q = front_cell_index; q != matrix[q].group; q = matrix[q].group);

                if(p == q) continue;

                if(matrix[p].sz < matrix[q].sz){
                    matrix[p].group = q;
                    matrix[q].sz += matrix[p].sz;
                    t = q;
                }
                else{
                    matrix[q].group = p;
                    matrix[p].sz += matrix[q].sz;
                    t = p;
                }

                for (p = cell_index; p != matrix[p].group; p = x) {
                    x = matrix[p].group;
                    matrix[p].group = t;
                }
                for (q = front_cell_index; q != matrix[q].group; q = x) {
                    x = matrix[q].group;
                    matrix[q].group = t;
                }
            }
            if(is_cell_in_board(row, column, i + 1, j) == TRUE && is_white(matrix[get_index(column, i + 1, j)]) == TRUE){
                under_cell_index = get_index(column, i + 1, j);
                
                // do search first
                for(p = cell_index; p != matrix[p].group; p = matrix[p].group);
                for(q = under_cell_index; q != matrix[q].group; q = matrix[q].group);

                if(p == q) continue;

                if(matrix[p].sz < matrix[q].sz){
                    matrix[p].group = q;
                    matrix[q].sz += matrix[p].sz;
                    t = q;
                }
                else{
                    matrix[q].group = p;
                    matrix[p].sz += matrix[q].sz;
                    t = p;
                }

                for (p = cell_index; p != matrix[p].group; p = x) {
                    x = matrix[p].group;
                    matrix[p].group = t;
                }
                for (q = under_cell_index; q != matrix[q].group; q = x) {
                    x = matrix[q].group;
                    matrix[q].group = t;
                }
            }
        }
    }
}

BOOL is_white(cell position)
{
    if(position.wall == 0){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

BOOL is_grey(cell position)
{
    if(position.wall > 0){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

BOOL is_black(cell position)
{
    if(position.wall == -1){
        return TRUE;
    }
    else{
        return FALSE;
    }
}