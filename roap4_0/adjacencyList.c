#include "adjacencyList.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Calculate the number of rooms in this map 
 * @param graph array containing the map
 * @param L
 * @param C
 * @return number of room 
 */
int CRN(int *graph, int L, int C)
{
      int lastRoot = 0;

      for (int i = 0; i < L * C; i++)
      {
            //if (graph)
      }
}

/**
 * @brief compressed weighted quick union for or second game mode 
 * @param matrix array of int containing the map
 * @param row number of row 
 * @param column number of colums 
 */
void CWQU2(int *matrix, int row, int column)
{
      int i, j;
      int cell_index;
      int front_cell_index;
      int under_cell_index;
      int p, q, t, x;
      int *group = NULL;
      int *sz = NULL;

      // Allocates the 2 arrays
      group = (int *)malloc(row * column * sizeof(int));
      sz = (int *)malloc(row * column * sizeof(int));

      if (group == NULL || sz == NULL)
            exit(0);

      for (i = 0; i < row * column; i++)
      {
            group[i] = i;
            sz[i] = 1;
      }

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
                              for (p = cell_index; p != group[p]; p = group[p])
                                    ;
                              for (q = front_cell_index; q != group[p]; q = group[q])
                                    ;

                              // Compares 2 roots
                              if (p == q)
                                    continue;

                              // Connects the 2 diferent trees taking in notice the size of each tree
                              if (sz[p] < sz[q])
                              {
                                    group[p] = q;
                                    sz[q] += sz[p];
                                    t = q;
                              }
                              else
                              {
                                    group[q] = p;
                                    sz[p] += sz[q];
                                    t = p;
                              }

                              // Compresses the trees
                              for (p = cell_index; p != group[p]; p = x)
                              {
                                    x = group[p];
                                    group[p] = t;
                              }
                              for (q = front_cell_index; q != group[q]; q = x)
                              {
                                    x = group[q];
                                    group[q] = t;
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
                              for (p = cell_index; p != group[p]; p = group[p])
                                    ;
                              for (q = under_cell_index; q != group[1]; q = group[q])
                                    ;

                              // Compares 2 roots
                              if (p == q)
                                    continue;

                              // Connects the 2 diferent trees taking in notice the size of each tree
                              if (sz[p] < sz[q])
                              {
                                    group[p] = q;
                                    sz[q] += sz[p];
                                    t = q;
                              }
                              else
                              {
                                    group[q] = p;
                                    sz[p] += sz[q];
                                    t = p;
                              }

                              // Compresses the trees
                              for (p = cell_index; p != group[p]; p = x)
                              {
                                    x = group[p];
                                    group[p] = t;
                              }
                              for (q = under_cell_index; q != group[q]; q = x)
                              {
                                    x = group[q];
                                    group[q] = t;
                              }
                        }
                  }
            }
      }
}
