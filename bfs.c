#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"
#include "lib.h"

bool BFS_connectable(int *graph, int v1, int v2, int L, int C)
{
    if(in_board(v2, L, C) && (I(v1, C) == I(v2, C) || J(v1, C) == J(v2, C)) && graph[v2] == 0) return true;
    else return false;
}

void streak_room(int *graph, int v, int L, int C, int room){
    edge *head = NULL;
    edge *tail = NULL;

    BFS_push(&head, &tail, v);
    
    while(head != NULL){
        v = BFS_pop(&head, &tail);
        graph[v] = room;
        if(BFS_connectable(graph, v, v - C, L, C) && !in_queue(head, v - C)) BFS_push(&head, &tail, v - C);
        if(BFS_connectable(graph, v, v + 1, L, C) && !in_queue(head, v + 1)) BFS_push(&head, &tail, v + 1);
        if(BFS_connectable(graph, v, v + C, L, C) && !in_queue(head, v + C)) BFS_push(&head, &tail, v + C);
        if(BFS_connectable(graph, v, v - 1, L, C) && !in_queue(head, v - 1)) BFS_push(&head, &tail, v - 1);
    }
    
}

void bfs(int *graph, int L, int C, int *N_rooms)
{
    int V = L * C;
    unsigned int i;
    int room = -2;
    for(i = 0; i < V; i++)
    {
        if(graph[i] == 0)
        {
            streak_room(graph, i, L, C, room);
            room--;
        }
    }
    *N_rooms = -1 * room - 2;
}
