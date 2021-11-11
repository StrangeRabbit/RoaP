#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue_array.h"
#include "lib.h"

bool BFS_connectable(int *graph, int v1, int v2, int L, int C)
{
    if(in_board(v2, L, C) && (I(v1, C) == I(v2, C) || J(v1, C) == J(v2, C)) && graph[v2] == 0) return true;
    else return false;
}

void streak_room(int *graph, int v, int L, int C, int room){
    int size = 2 * L + 2 * C;
    int *queue = init_queue(2 * L + 2 * C);
    int pusher = 0;
    int poper = 0;
    graph[v] = room;
    push(&pusher, size, queue, v);
    
    while(poper != pusher){
        v = pop(&poper, size, queue, v);
        if(BFS_connectable(graph, v, v - C, L, C)) {
            graph[v - C] = room;
            push(&pusher, size, queue, v - C);
        }
        if(BFS_connectable(graph, v, v - 1, L, C)){
            graph[v - 1] = room; 
            push(&pusher, size, queue, v - C);
        }
        if(BFS_connectable(graph, v, v + 1, L, C)){
            graph[v + 1] = room;
            push(&pusher, size, queue, v + 1);
        } 
        if(BFS_connectable(graph, v, v + C, L, C)){
            graph[v + C] = room; 
            push(&pusher, size, queue, v + C);
        }
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
