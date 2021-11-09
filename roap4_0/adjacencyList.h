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

int CRN(int *graph, int L, int C, int *group);
int getRoot(int *group, int i);
bool id_white(int aux);
int *CWQU2(int *matrix, int row, int column, int *group, int *sz);
int same_root2(int *matrix, int *group, int i1, int j1, int i2, int j2, int column);
list *updateListCost(list *array, int group, int cost, int i, int j);
list **toSmallerMap(int NumberOfRooms, int *group, int *graph, int L, int C);
void freeMatrix(list **array, int V);
void printFullList(list **array, int V);

#endif