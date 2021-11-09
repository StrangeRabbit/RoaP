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
      int lastOldRoot = 0;
      int newRoot = -1;
      int p = 0;

      for (unsigned int i = 0; i < L * C; i++)
      {
            p = getRoot(group, i);
            if (lastOldRoot < p)
            {
                  newRoot += 1;
                  group[i] = newRoot;
                  lastOldRoot = p;
                  for (unsigned int j = i; j < L * C; j++)
                  {
                        if (group[j] == p)
                              group[j] = newRoot;
                  }
            }
      }

      return newRoot;
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
            else
                  group[i] = -1;
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
                              if (p != q)
                              {

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
                              if (p != q)
                              {

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

list **toSmallerMap(int NumberOfRooms, int *group, int *graph, int L, int C)
{
      list **array = (list **)malloc(NumberOfRooms * sizeof(list *));

      for (unsigned int i = 0; i < L; i++)
      {
            for (unsigned int j = 0; j < C; j++)
            {
                  if (is_cell_in_board(L, C, i, j + 2))
                  {
                        if (graph[i * C + j] != 0 && graph[i * C + j + 2])
                              if (group[i * C + j] != group[i * C + j + 2]) // temos uma parede no meio
                              {
                                    array[group[i * C + j]] = updateListCost(array[group[i * C + j]], group[i * C + j + 2], graph[i * C + j + 1], i, j + 1);
                                    array[group[i * C + j + 2]] = updateListCost(array[group[i * C + j + 2]], group[i * C + j], graph[i * C + j + 1], i, j + 1);
                              }
                  }
                  if (is_cell_in_board(L, C, i + 2, j))
                  {
                        if (graph[i * C + j] == 0 && graph[(i + 2) * C + j])
                              if (group[i * C + j] != group[(i + 2) * C + j]) // temos uma parede no meio
                              {
                                    array[group[i * C + j]] = updateListCost(array[group[i * C + j]], group[(i + 2) * C + j], graph[(i + 1) * C + j], i + 1, j);
                                    array[group[(i + 2) * C + j]] = updateListCost(array[group[(i + 2) * C + j]], group[i * C + j], graph[(i + 1) * C + j], i + 1, j);
                              }
                  }
            }
      }
      free(graph);
      free(group);
      return array;
}

list *updateListCost(list *array, int group, int cost, int i, int j)
{
      list *aux = array;
      list *newNode = NULL;
      if (aux != NULL)
      {

            while (aux != NULL)
            {
                  if (aux->vertice == group && cost > aux->cost)
                  {
                        aux->cost = cost;
                        aux->vertice = group;
                        aux->i = i;
                        aux->j = j;
                  }
                  aux = aux->next;
            }

            if (aux == NULL) // não estavam ligados
            {
                  newNode = (list *)malloc(sizeof(list) * 1);
                  if (newNode == NULL)
                        exit(0);

                  newNode->next = NULL;
                  newNode->vertice = group;
                  newNode->cost = cost;
                  newNode->i = i;
                  newNode->j = j;

                  aux = array->next;
                  array->next = newNode;
                  newNode->next = aux;
            }
      }
      else
      {

            array = (list *)malloc(1 * sizeof(list));
            array->cost = cost;
            array->vertice = group;
            array->next = NULL;
      }

      return array;
}

void freeMatrix(list **array, int V)
{
      list *aux;
      for (int i = 0; i < V; i++)
      {
            while (array[i] != NULL)
            {
                  aux = array[i];
                  array[i] = aux->next;
                  free(aux);
            }
      }
      free(array);
      return;
}