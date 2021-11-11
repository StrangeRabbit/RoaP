#ifndef _QUEUE_
#define _QUEUE_

typedef struct _edge
{
    int v;
    struct _edge *next;
} edge;

bool in_queue(edge *head, int v);
int BFS_pop(edge **head, edge **tail);
void BFS_push(edge **head, edge **tail, int v);

#endif