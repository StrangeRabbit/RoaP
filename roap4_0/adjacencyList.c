#include "game_mode.h"
#include "adjacencyList.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Calculate the number of rooms in this map and changes their root to the new one
 * @param graph array containing the map
 * @param L number of lines
 * @param C number of columns
 * @return number of room 
 */
int CRN(int *graph, int L, int C, int *group)
{
      // Variable Declaration
      int lastOldRoot = 0;
      int newRoot = 0;
      int p = 0;
      int flag;

      int V = L * C;

      // Goes throug all the vertices in the array
      for (unsigned int i = 0; i < V; i++)
      {
            // only changes if is white
            if (id_white(graph[i]))
            {

                  p = getRoot(group, i);

                  // Check if it is a new room or not, since all new rooms will have bigger root
                  if (lastOldRoot < p)
                  {
                        newRoot += 1;
                        lastOldRoot = p;
                        flag = 1;

                        // Changes all the other vertices with this root
                        for (unsigned int j = i; j < V; j++)
                        {
                              if (group[j] == p)
                              {
                                    group[j] = newRoot;
                                    flag = 0;
                              }
                              if (j % C == 0)
                              {
                                    if (flag)
                                          break;
                                    flag = 1;
                              }
                        }
                  }
            }
      }

      // Return the number of rooms
      return ++newRoot;
}

/**
 * @brief compressed weighted quick union for or second game mode 
 * @param matrix array of int containing the map
 * @param row number of row 
 * @param column number of colums 
 */
int *CWQU2(int *matrix, int row, int column, int *group, int *sz)
{
      // Variable declaration
      int i, j;
      int cell_index;
      int front_cell_index;
      int under_cell_index;
      int p, q, t, x;

      // Inicializes all the arrays with correct value
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
      // free Size array and return group array
      free(sz);
      return group;
}

/**
 * @brief Check if it is white
 * @param aux number to be checked
 * @return true if is white, false otherwise
 */
bool id_white(int aux)
{
      if (aux == 0)
            return true;
      return false;
}

/**
 * @brief Check if two vertices in the array have the same root
 * @param matrix array containing the map
 * @param group array containing the roots of the vertices\\
 * @param i1 line of first vertice
 * @param j1 column of first vertice
 * @param i2 line of second vertice
 * @param j2 column of second vertice
 * @param column number of columns in the map
 * @param line number of lines in the map
 * @return 1 if the they have the same root, 0 otherwise
 */
int same_root2(int *matrix, int *group, int i1, int j1, int i2, int j2, int column, int line)
{
      int p = i1 * column + j1;
      int q = i2 * column + j2; // Gets two roots of the tree

      if (is_cell_in_board(line, column, i1, j1) && is_cell_in_board(line, column, i2, j2))
      {
            p = getRoot(group, p);
            q = getRoot(group, q);
      }
      else
      {
            return 0;
      }

      // Checks the roots
      if (p == q)
            return 1;
      else
            return 0;
}

/**
 * @brief Gets the root of a certain vertice in the array 
 * @param group array containg all the root
 * @param i vertice we want to know root of
 * @return root of the value
 */
int getRoot(int *group, int i)
{
      int p;
      // Makes sure i is not a wall
      if (i < 0)
            return -1;

      // Goes from up in the tree to get the root
      for (p = i; p != group[p]; p = group[p])
            if (group[p] < 0)
                  return -1;

      return p;
}

/**
 * @brief Takes the first graph of V position and moves it to a V/2 adjacency list
 * @param NumberOfRooms number of rooms  in a map
 * @param group Array containing the root of the vertices
 * @param graph Graph containing the first map in (V vertices)
 * @param L number of lines in the map
 * @param C number of column in the mao
 * @return Adjacency list of the first graph
 */
list **toSmallerMap(int NumberOfRooms, int *group, int *graph, int L, int C)
{
      // Creates the adjacency list
      list **array = (list **)malloc(NumberOfRooms * sizeof(list *));
      for (unsigned int i = 0; i < NumberOfRooms; i++)
            array[i] = NULL;

      // Goes through the lines
      for (unsigned int i = 0; i < L; i++)
      {
            // Goes through the columns
            for (unsigned int j = 0; j < C; j++)
            {
                  // Check if is in board
                  if (is_cell_in_board(L, C, i, j + 2))
                  {
                        // Checks if the condition to connect two rooms are done
                        if (graph[i * C + j] == 0 && graph[i * C + j + 2] == 0 && graph[i * C + j + 1] != -1)
                              // confirms if there are 2 diferent rooms side by side
                              if (group[i * C + j] != group[i * C + j + 2])
                              {
                                    array[group[i * C + j]] = updateListCost(array[group[i * C + j]], group[i * C + j + 2], graph[i * C + j + 1], i, j + 1);
                                    array[group[i * C + j + 2]] = updateListCost(array[group[i * C + j + 2]], group[i * C + j], graph[i * C + j + 1], i, j + 1);
                              }
                  }
                  //Checks if is in board
                  if (is_cell_in_board(L, C, i + 2, j))
                  {
                        // Checks if the condition to connect two rooms are done
                        if (graph[i * C + j] == 0 && graph[(i + 2) * C + j] == 0 && graph[(i + 1) * C + j] != -1)
                              // confirms if there are 2 diferent rooms one on top of the other
                              if (group[i * C + j] != group[(i + 2) * C + j])
                              {
                                    array[group[i * C + j]] = updateListCost(array[group[i * C + j]], group[(i + 2) * C + j], graph[(i + 1) * C + j], i + 1, j);
                                    array[group[(i + 2) * C + j]] = updateListCost(array[group[(i + 2) * C + j]], group[i * C + j], graph[(i + 1) * C + j], i + 1, j);
                              }
                  }
            }
      }
      // Free all useless memory && returns array
      free(graph);
      free(group);
      return array;
}

/**
 * @brief updated the adjacency list of a vertice
 * @param array pointer to the head of the list to be updated
 * @param group vertice that need to be added to the list
 * @param cost cost of the egde to be tested
 * @param i line of the edge in the original map
 * @param j column of the edge in the original map
 * @return updated list
 */
list *updateListCost(list *array, int group, int cost, int i, int j)
{
      list *aux = array;
      list *newNode = NULL;

      // Check if we have a list already
      while (aux != NULL)
      {
            // Updates vertice connection values
            if (aux->vertice == group)
            {
                  if (cost < aux->cost)
                  {
                        aux->cost = cost;
                        aux->i = i;
                        aux->j = j;
                  }
                  break;
            }
            aux = aux->next;
      }
      // inserts an element into the list if need be (list was not created || connection to the vertice was non existent)
      if (aux == NULL)
      {
            newNode = (list *)malloc(1 * sizeof(list));
            if (newNode == NULL)
                  exit(0);
            newNode->cost = cost;
            newNode->vertice = group;
            newNode->i = i;
            newNode->j = j;
            newNode->next = array;
            array = newNode;
      }
      return array;
}

/**
 * @brief delets all the adjacency List memory
 * @param array adjaceny list
 * @param V number of vertices
 */
void freeMatrix(list **array, int V)
{
      list *aux;
      if (array != NULL)
      {
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
      }
      return;
}
