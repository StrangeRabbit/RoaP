#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib.h"

/** 
 * @brief Check if a position in the map is a wall or not
 * @param V vertice to check 
 * @param graph map containing the labyrithn
 * @return true if it is not a wall, false otherwise
 */
bool white(int V, int *graph)
{
    if (graph[V] == 0)
        return true;
    return false;
}

/** 
 * @brief return the line index to a 2D array 
 * @param idx position to check array 
 * @param C number of columns int the map
 * @return line index
 */
int I(int idx, int C)
{
    return idx / C;
}

/** 
 * @brief Calculates the column number to a 2D
 * @param idx position to check array 
 * @param C number of columns
 * @return column index
 */
int J(int idx, int C)
{
    return idx % C;
}

/** 
 * @brief Calculates 1D array index bases on 2 coordinates
 * @param i line of the 2D array
 * @param j column of the 2D array
 * @param C number of column in the map
 * @return 1D array coordinates
 */
int idx(int i, int j, int C)
{
    return i * C + j;
}

/**
 * @brief Check if a wall is breakable or not 
 * @param graph containing the array
 * @param V  vertice index 
 * @param C number of columns 
 * @param L number of lines in the map
 * @return true if is breakable, flase otherwise
 */
bool breakable(int *graph, int v, int C, int L)
{
    if (I(v + 1, C) == I(v - 1, C))
        if (graph[v + 1] == 0 && graph[v - 1] == 0)
            return true;
    if (I(v + C, C) < L && I(v - C, C) > -1 && v - C > -1)
        if (graph[v + C] == 0 && graph[v - C] == 0)
            return true;
    return false;
}

/**
 * @brief Check if a wall is in the board
 * @param v index vertice to check 
 * @param L line numbers
 * @param C column number
 * @return true if it is in board, false otherwise
 */
bool in_board(int v, int L, int C)
{
    int V = L * C, i = I(v, C);
    if (i < L && i > -1 && v > -1 && v < V)
        return true;
    else
        return false;
}

/**
 * @brief jump a map if there is no need to allocated it 
 * @param fp pointer to the file that will be jumped 
 * @param P number of walls to jump 
 */
void jump_map(FILE *fp, int P)
{
    int a, i, j, v;
    for (a = 0; a < P; a++)
    {
        if (fscanf(fp, "%d %d %d", &i, &j, &v) != 3)
            exit(0);
    }
}
