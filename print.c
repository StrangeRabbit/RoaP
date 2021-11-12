#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "print.h"
#include "lib.h"
#include "list.h"

/**
 * @brief Recursive function to print wall destroied walls in the map
 * @param list Edge vertice matrix where the cost and index of walls are inserted
 * @param treasure index of the treasure in the map
 * @param ofp Output file pointer
 * @param C number of columns in the map
 * @param walls number of walls already counted an ready to be insert
 */

void printWalls(_room **list, int *parent, int treasure, FILE *ofp, int C, int walls)
{
      _room *aux = list[treasure];
      if (parent[treasure] != 0)
      {
            printWalls(list, parent, parent[treasure], ofp, C, ++walls);
      }
      else
      {
            fprintf(ofp, "%d\n", ++walls);
      }

      while (aux->room != parent[treasure] && aux != NULL)
            aux = aux->next;

      fprintf(ofp, "%d %d %d\n", I(aux->v, C) + 1, J(aux->v, C) + 1, aux->cost);
      return;
}