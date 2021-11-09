#ifndef ADJACENCYLIST
#define ADJACENCYLIST

typedef struct _list
{
      int cost;
      int vertice; // equivalent to root if it helps to thinks this way :)
      list *next;
} list;

int CRN(int *graph, int L, int C);
void CWQU2(int *matrix, int row, int column);

#endif