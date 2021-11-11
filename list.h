#ifndef __LIST__
#define __LIST__

#include "queue.h"

typedef struct _ROOM{
    int room;
    int v;
    int cost;
    struct _ROOM *next;
} _room;

_room **create_list(int *graph, int rooms, edge *head, edge *tail, int L, int C);
void free_list(_room **list, int rooms);

#endif