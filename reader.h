#ifndef __READER__
#define __READER__

#include "queue.h"

void header(FILE *fp, int *i, int *j, int *P);
void read_file(FILE *fp, int **graph, int P, int L, int C, int *queue[], int size, int *pusher);

#endif