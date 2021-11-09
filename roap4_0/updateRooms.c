#include <stdio.h>
#include <stdlib.h>

#include "adjacencyList.h"

void updateRooms(int *graph, int V)
{
    int last_room = graph[0];
    int new_room = 0;
    unsigned int i, j;
    for(i = 1; i < V; i++){
        if(graph[i] == last_room) graph[i] = new_room;
    }
    for(i = 1; i < V; i++){
        if(graph[i] > last_room) {
            last_room = graph[i];
            new_room++;
            for(j = i; j < V; j++){
                if(graph[j] == last_room) graph[j] = new_room;
            }
        }

    }
}