#include "game_mode.h"
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
int CRN(int *graph, int L, int C, int *group)
{
      int lastRoot = -1;
      int aux = 0;
      int p = 0;

      /*
      for (int i = 0; i < L; i++)
      {
            for (int j = 0; j < C; j++)
            {
                  printf("%d ", group[i * C + j]);
            }
            printf("\n");
      }*/

      for (int i = 0; i < L * C; i++)
      {
            if (graph[i] == 0)
            {
                  p = getRoot(group, i);
                  if (p > lastRoot)
                  {
                        lastRoot = p;
                        aux++;
                  }
            }
      }
      return aux;
}

/**
 * @brief compressed weighted quick union for or second game mode 
 * @param matrix array of int containing the map
 * @param row number of row 
 * @param column number of colums 
 */
int *CWQU2(int *matrix, int row, int column, int *group, int *sz)
{
      int i, j;
      int cell_index;
      int front_cell_index;
      int under_cell_index;
      int p, q, t, x;

      for (i = 0; i < row * column; i++)
      {

            if (matrix[i] == 0)
            {
                  sz[i] = 1;
                  group[i] = i;
            }
      }

      // Moves through the map
      for (i = 0; i < row; i++)
      {
            for (j = 0; j < column; j++)
            {
                  cell_index = i * column + j;
                  // Only check connects the cell if it is not a wall
                  if (id_white(matrix[cell_index]) == false)
                        continue;
                  // Only connects if the cell is in the board
                  if (is_cell_in_board(row, column, i, j + 1) == true)
                  {
                        if (id_white(matrix[i * column + j + 1]) == true)
                        {
                              // Gets the index of the cell that has index +1
                              front_cell_index = (i * column + j + 1);

                              //  Gets the 2 roots of the trees
                              for (p = cell_index; p != group[p]; p = group[p])
                                    ;
                              for (q = front_cell_index; q != group[q]; q = group[q])
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
                        if (id_white(matrix[(i + 1) * column + j]) == true)
                        {
                              under_cell_index = (i + 1) * column + j;

                              //  Gets the 2 roots of the trees
                              for (p = cell_index; p != group[p]; p = group[p])
                                    ;
                              for (q = under_cell_index; q != group[q]; q = group[q])
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
      free(sz);
      return group;
}

bool id_white(int aux)
{
      if (aux == 0)
            return true;
      return false;
}

int same_root2(int *matrix, int *group, int i1, int j1, int i2, int j2, int column)
{
      int p = i1 * column + j1;
      int q = i2 * column + j2; // Gets two roots of the tree

      p = getRoot(group, p);
      q = getRoot(group, q);

      // Checks the roots
      if (p == q)
            return 1;
      else
            return 0;
}

int getRoot(int *group, int i)
{
      int p;

      for (p = i; p != group[p]; p = group[p])
            ;

      return p;
}