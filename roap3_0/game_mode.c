#include <stdio.h>
#include <stdlib.h>

#include "game_mode.h"
#include "input.h"

/**
 * @brief Confirms two given position are in the board
 * @param row number of rows in the map
 * @param column numer of columns in the map 
 * @param i row that the cell is in
 * @param j column that the cell is in
 * @return true if cell is in the map, otherwise false
 */
bool is_cell_in_board(int row, int column, int i, int j)
{
    if (i > row - 1 || i < 0 || j > column - 1 || j < 0)
        return false;
    else
        return true;
}

/**
 * @brief Controls game mode A1
 * @param fp pointer to the output file 
 * @param matrix array contain the labyrinth 
 * @param i row the cell is in
 * @param j column the cell is in
 * @param row number of rows in map
 * @param column number of column in the map
 * @return VOID
 */
void mode_A1(FILE *fp, cell *matrix, int i, int j, int row, int column)
{
    int cell_type = -2;
    if (is_cell_in_board(row, column, i, j) == false)
    {
        fprintf(fp, "%d\n\n", cell_type);
    }
    else
    {
        fprintf(fp, "%d\n\n", matrix[get_index(column, i, j)].wall);
    }
    return;
}

/**
 * @brief Controls game mode A2
 * @param fp pointer to the output file 
 * @param matrix array contain the labyrinth 
 * @param i row the cell is in
 * @param j column the cell is in
 * @param row number of rows in map
 * @param column number of column in the map
 * @return VOID
 */
void mode_A2(FILE *fp, cell *matrix, int i, int j, int row, int column)
{
    unsigned int p;
    int flag = 0;
    // way of compress code
    int around_x[] = {-1, 0, 1, 0};
    int around_y[] = {0, 1, 0, -1};
    if (is_cell_in_board(row, column, i, j) == false)
        flag = -2;
    else
    {
        // check 4 positions around the cell
        // only need 1 of them to match the sentence
        for (p = 0; p < 4; p++)
        {
            if (is_cell_in_board(row, column, i + around_y[p], j + around_x[p]) == false)
                continue;
            if (is_white(matrix[get_index(column, i + around_y[p], j + around_x[p])]) == true)
                flag = 1;
        }
    }
    fprintf(fp, "%d\n\n", flag);
    return;
}

/**
 * @brief Controls game mode A3
 * @param fp pointer to the output file 
 * @param matrix array contain the labyrinth 
 * @param i row the cell is in
 * @param j column the cell is in
 * @param row number of rows in map
 * @param column number of column in the map
 * @return VOID
 */
void mode_A3(FILE *fp, cell *matrix, int i, int j, int row, int column)
{
    unsigned int p;
    int flag = 0;
    // way of compress code
    int around_x[] = {-1, 0, 1, 0};
    int around_y[] = {0, 1, 0, -1};
    if (is_cell_in_board(row, column, i, j) == false)
        flag = -2;
    else
    {
        // check 4 positions around the cell
        // only need 1 of them to match the sentence
        for (p = 0; p < 4; p++)
        {
            if (is_cell_in_board(row, column, i + around_y[p], j + around_x[p]) == false)
                continue;
            if (is_grey(matrix[get_index(column, i + around_y[p], j + around_x[p])]) == true)
                flag = 1;
        }
    }
    fprintf(fp, "%d\n\n", flag);
    return;
}

/**
 * @brief Controls game mode A4
 * @param fp pointer to the output file 
 * @param matrix array contain the labyrinth 
 * @param i row the cell is in
 * @param j column the cell is in
 * @param row number of rows in map
 * @param column number of column in the map
 * @return VOID
 */
void mode_A4(FILE *fp, cell *matrix, int i, int j, int row, int column)
{
    unsigned int p;
    int flag = 0;
    // way of compress code
    int around_x[] = {-1, 0, 1, 0};
    int around_y[] = {0, 1, 0, -1};
    if (is_cell_in_board(row, column, i, j) == false)
        flag = -2;
    else
    {
        // check 4 positions around the cell
        // only need 1 of them to match the sentence
        for (p = 0; p < 4; p++)
        {
            if (is_cell_in_board(row, column, i + around_y[p], j + around_x[p]) == false)
                continue;
            if (is_black(matrix[get_index(column, i + around_y[p], j + around_x[p])]) == true)
                flag = 1;
        }
    }
    fprintf(fp, "%d\n\n", flag);
    return;
}

/**
 * @brief Controls game mode A2
 * @param fp pointer to the output file 
 * @param matrix array contain the labyrinth 
 * @param i row the cell is in
 * @param j column the cell is in
 * @param row number of rows in map
 * @param column number of column in the map
 * @return VOID
 */
void mode_A5(FILE *fp, cell *matrix, int i, int j, int row, int column)
{
    int flag = 0;
    if (is_cell_in_board(row, column, i, j) == false)
        flag = -2;
    else if (is_grey(matrix[get_index(column, i, j)]) == false)
        flag = -1;
    else
    {
        // just need 1 of the sentences true
        // if left and right cells are white the wall can be broken
        if (is_cell_in_board(row, column, i, j - 1) == true && is_cell_in_board(row, column, i, j + 1) == true)
            if (is_white(matrix[get_index(column, i, j + 1)]) == true && is_white(matrix[get_index(column, i, j - 1)]) == true)
                flag = 1;
        // if up and down cells are white the wall can be broken
        if (is_cell_in_board(row, column, i + 1, j) == true && is_cell_in_board(row, column, i - 1, j) == true)
            if (is_white(matrix[get_index(column, i + 1, j)]) == true && is_white(matrix[get_index(column, i - 1, j)]) == true)
                flag = 1;
    }
    fprintf(fp, "%d\n\n", flag);
    return;
}

/**
 * @brief Controls game mode A6
 * @param fp pointer to the output file 
 * @param matrix array contain the labyrinth 
 * @param i1 row the fisrt cell is in
 * @param j1 column the first cell is in
 * @param i2 row the second cell is in
 * @param j2 column the second cell is in
 * @param row number of rows in map
 * @param column number of column in the map
 * @return VOID
 */
void mode_A6(FILE *fp, cell *matrix, int i1, int j1, int i2, int j2, int row, int column)
{
    int flag;
    if (is_cell_in_board(row, column, i1, j1) == false || is_cell_in_board(row, column, i2, j2) == false)
    {
        flag = -2;
    }
    else
    {
        //connect all rooms with a compressed weighted quick union
        CWQU(matrix, row, column);

        flag = same_root(matrix, row, column, i1, j1, i2, j2);
    }
    fprintf(fp, "%d\n\n", flag);
    return;
}

/**
 * @brief After using CWQU we check if we have the same root for 2 cells
 * @param matrix array contain the labyrinth 
 * @param column number of column in the map
 * @param row number of rows in map
 * @param i1 row the fisrt cell is in
 * @param j1 column the first cell is in
 * @param i2 row the second cell is in
 * @param j2 column the second cell is in
 * @return 1 if p && q have the same root 
 */
int same_root(cell *matrix, int row, int column, int i1, int j1, int i2, int j2)
{
    int cell1 = get_index(column, i1, j1);
    int cell2 = get_index(column, i2, j2);
    int p, q;

    // Gets two roots of the tree
    for (p = cell1; p != matrix[p].group; p = matrix[p].group)
        ;
    for (q = cell2; q != matrix[q].group; q = matrix[q].group)
        ;

    // Checks the roots
    if (p == q)
        return 1;
    else
        return 0;
}

/**
 * @brief After using CWQU we check if we have the same root for 2 cells
 * @param matrix array contain the labyrinth 
 * @param column number of column in the map
 * @param row number of rows in map
 * @return VOID
 */

void CWQU(cell *matrix, int row, int column)
{
    int i, j;
    int cell_index;
    int front_cell_index;
    int under_cell_index;
    int p, q, t, x;
    // Moves through the map
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            cell_index = get_index(column, i, j);

            // Only check connects the cell if it is not a wall
            if (is_white(matrix[cell_index]) == false)
                continue;
            // Only connects if the cell is in the board
            if (is_cell_in_board(row, column, i, j + 1) == true)
            {
                if (is_white(matrix[get_index(column, i, j + 1)]) == true)
                {
                    // Gets the index of the cell that has index +1
                    front_cell_index = get_index(column, i, j + 1);

                    //  Gets the 2 roots of the trees
                    for (p = cell_index; p != matrix[p].group; p = matrix[p].group)
                        ;
                    for (q = front_cell_index; q != matrix[q].group; q = matrix[q].group)
                        ;

                    // Compares 2 roots
                    if (p == q)
                        continue;

                    // Connects the 2 diferent trees taking in notice the size of each tree
                    if (matrix[p].sz < matrix[q].sz)
                    {
                        matrix[p].group = q;
                        matrix[q].sz += matrix[p].sz;
                        t = q;
                    }
                    else
                    {
                        matrix[q].group = p;
                        matrix[p].sz += matrix[q].sz;
                        t = p;
                    }

                    // Compresses the trees
                    for (p = cell_index; p != matrix[p].group; p = x)
                    {
                        x = matrix[p].group;
                        matrix[p].group = t;
                    }
                    for (q = front_cell_index; q != matrix[q].group; q = x)
                    {
                        x = matrix[q].group;
                        matrix[q].group = t;
                    }
                }
            }
            // only connecrs if cell with index + number of columns in the map && is white
            if (is_cell_in_board(row, column, i + 1, j) == true)
            {
                if (is_white(matrix[get_index(column, i + 1, j)]) == true)
                {
                    under_cell_index = get_index(column, i + 1, j);

                    //  Gets the 2 roots of the trees
                    for (p = cell_index; p != matrix[p].group; p = matrix[p].group)
                        ;
                    for (q = under_cell_index; q != matrix[q].group; q = matrix[q].group)
                        ;

                    // Compares 2 roots
                    if (p == q)
                        continue;

                    // Connects the 2 diferent trees taking in notice the size of each tree
                    if (matrix[p].sz < matrix[q].sz)
                    {
                        matrix[p].group = q;
                        matrix[q].sz += matrix[p].sz;
                        t = q;
                    }
                    else
                    {
                        matrix[q].group = p;
                        matrix[p].sz += matrix[q].sz;
                        t = p;
                    }

                    // Compresses the trees
                    for (p = cell_index; p != matrix[p].group; p = x)
                    {
                        x = matrix[p].group;
                        matrix[p].group = t;
                    }
                    for (q = under_cell_index; q != matrix[q].group; q = x)
                    {
                        x = matrix[q].group;
                        matrix[q].group = t;
                    }
                }
            }
        }
    }
}

/**
 * @brief Confirms if a cell is white 
 * @param position Cell that is to be confirmed 
 * @return true if position is white false if position is not 
 */
bool is_white(cell position)
{
    if (position.wall == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Confirms if a cell is grey 
 * @param position Cell that is to be confirmed 
 * @return true if position is whigreyte false if position is not 
 */
bool is_grey(cell position)
{
    if (position.wall > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Confirms if a cell is black 
 * @param position Cell that is to be confirmed 
 * @return true if position is black false if position is not
 */
bool is_black(cell position)
{
    if (position.wall == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Confirms if treasure cell is adjacent to starting point (0,0)
 * @param i line of trease cell
 * @param j column of treasure cell
 * @return true if cell adjacent, falsez otherwise
 */

bool treasure_is_adjacent_to_src(int i, int j)
{
    if ((i == 0 && j == 1) || (i == 1 && j == 0))
        return true;
    return false;
}
