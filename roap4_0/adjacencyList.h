#ifndef ADJACENCYLIST
#define ADJACENCYLIST

typedef struct _list
{
      int cost;
      int i;
      int j;
      int vertice; // equivalent to root if it helps to thinks this way :)
      struct _list *next;
} list;

int same_root2(int *matrix, int *group, int i1, int j1, int i2, int j2, int column, int line);
int *CWQU2(int *matrix, int row, int column, int *group, int *sz);
int CRN(int *graph, int L, int C, int *group);
int getRoot(int *group, int i);

list **toSmallerMap(int NumberOfRooms, int *group, int *graph, int L, int C);
list *updateListCost(list *array, int group, int cost, int i, int j);

bool id_white(int aux);

void printFullList(list **array, int V);

#endif