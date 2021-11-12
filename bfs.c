#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue_array.h"
#include "lib.h"

/** 
 * @brief check if 2 position in the board are connectable
 * @param graph Map of the labyrinth
 * @param v1 vertice 1
 * @param v2 vertice 2
 * @param L lines in the map
 * @param C columns in the map
 * @return true if they are connectable, false otherwise 
 */
bool BFS_connectable(int *graph, int v1, int v2, int L, int C)
{
    if (in_board(v2, L, C) && (I(v1, C) == I(v2, C) || J(v1, C) == J(v2, C)) && graph[v2] == 0)
        return true;
    else
        return false;
}

/**
 * @brief connect a certain room in the map
 * @param graph Map of the labyrinth
 * @param v first vertice of the room 
 * @param L lines in the map
 * @param C columns in the map 
 * @param room root the room is suposed to have (first root is -2)
 */
void streak_room(int *graph, int v, int L, int C, int room)
{
    int size = 2 * L + 2 * C;
    int *queue = init_queue(2 * L + 2 * C);
    int pusher = 0;
    int poper = 0;
    graph[v] = room;
    ARRAY_push(&pusher, size, queue, v);

    // Continues the loop while the queue is not empty
    while (poper != pusher)
    {
        // Gets one element from the queue
        v = ARRAY_pop(&poper, size, queue);
        // Check if we can connect the position right above
        if (BFS_connectable(graph, v, v - C, L, C))
        {
            // If so changes room value to the suposed root and puts it in the quere
            graph[v - C] = room;
            ARRAY_push(&pusher, size, queue, v - C);
        }
        // Check if we can connect the position right above
        if (BFS_connectable(graph, v, v + 1, L, C))
        {
            // If so changes room value to the suposed root and puts it in the quere
            graph[v + 1] = room;
            ARRAY_push(&pusher, size, queue, v + 1);
        }
        // Check if we can connect the position right above
        if (BFS_connectable(graph, v, v + C, L, C))
        {
            // If so changes room value to the suposed root and puts it in the quere
            graph[v + C] = room;
            ARRAY_push(&pusher, size, queue, v + C);
        }
        // Check if we can connect the position right above
        if (BFS_connectable(graph, v, v - 1, L, C))
        {
            // If so changes room value to the suposed root and puts it in the quere
            graph[v - 1] = room;
            ARRAY_push(&pusher, size, queue, v - 1);
        }
    }
    // Queue is empty so it can be freed
    free_queue(queue);
}

/** 
 * @brief functon that controls the bfs 
 * @param graph Map of the labyrinth
 * @param L number of Lines
 * @param C columns
 * @param N_rooms pointer to an interger that will have the number of room  
 * @return void 
 */
void bfs(int *graph, int L, int C, int *N_rooms)
{
    int V = L * C;
    unsigned int i;
    int room = -2;

    // Cicle to make sure all vertices are connect
    for (i = 0; i < V; i++)
    {
        // Check it is to be connectd
        if (graph[i] == 0)
        {
            streak_room(graph, i, L, C, room);
            room--;
        }
    }
    *N_rooms = -1 * room - 2;
}
