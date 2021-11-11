#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "print.h"
#include "lib.h"
#include "list.h"

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