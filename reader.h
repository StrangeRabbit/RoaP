#ifndef __READER__
#define __READER__

#include "queue.h"

void header(FILE *fp, int *i, int *j, int *P);
void read_file(FILE *fp, int **graph, char *filename, int P, int L, int C, edge **head, edge **tail);

#endif