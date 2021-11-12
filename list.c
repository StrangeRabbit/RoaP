#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"
#include "lib.h"
#include "queue.h"

/**
 * @brief check if 2 points are connectable
 * 
 * @param graph graph
 * @param v1 vertice to connect
 * @param v2 vertice to connect
 * @param L lines of graph
 * @param C columns of graph
 * @return true if connectable
 * @return false if not connectable
 */
bool LIST_connectable(int *graph, int v1, int v2, int L, int C)
{
    if( in_board(v1, L, C) && \
        in_board(v2, L, C) && \
        (I(v1, C) == I(v2, C) || J(v1, C) == J(v2, C)) && \
        graph[v1] < -1 && \
        graph[v2] < -1 && graph[v1] != graph[v2]) 
        return true;
    else return false;
}

/**
 * @brief convert paint of room to position in the adjacency list
 * 
 * @param room number of the room
 * @return int position in the list
 */
int list_room(int room)
{
    return room * (-1) - 2;
}

/**
 * @brief insert a room in the list of a vertice
 * 
 * @param list adjacency list
 * @param room room to add
 * @param v vertice of the list to add
 * @param cost cost of the edge
 */
void insert(_room **list, int room, int v, int cost)
{
    _room *aux = (_room*) malloc(sizeof(_room));
    if(aux == NULL) exit(0);
    aux->room = room;
    aux->v = v;
    aux->cost = cost;
    aux->next = *list;
    *list = aux;
}

/**
 * @brief check if a vertice is already in a list
 * 
 * @param list adjancecy list
 * @param v vertice to check
 * @return pointer to the vertice if exists or NULL if doesnt exist
 */
_room *in_list(_room *list, int v)
{
    /* search for the vertice */
    while(list != NULL)
    {
        if(list->room == v) return list;
        list = list->next;
    }
    return NULL;
}

/**
 * @brief Create an adjancency list
 * 
 * @param graph graph to convert
 * @param rooms number of rooms
 * @param queue queue of walls
 * @param poper pop position
 * @param pusher push position
 * @param size size of wall queue
 * @param L number of lines of the graph
 * @param C number of lines of the columns
 * @return adjancenct list
 */
_room **create_list(int *graph, int rooms, int *queue, int *poper, int *pusher, int size, int L, int C)
{
    int i, v, v1, v2, room1, room2;
    _room *pos1, *pos2;

    /* allocate and init the adjancency list */
    _room **list = (_room**) malloc(rooms * sizeof(_room*));
    for(i = 0; i < rooms; i++)
        list[i] = NULL;
    
    /* pop all walls */
    while (*pusher != *poper)
    {
        v = ARRAY_pop(poper, size, queue);
        
        v1 = v - 1;
        v2 = v + 1;
        
        room1 = 0;
        room2 = 0;
        /* connect side rooms and up/down rooms */
        for(i = 0; i < 2; i++, v1 = v - C, v2 = v + C){
            /* connect rooms if connectable */
            if(LIST_connectable(graph, v1, v2, L, C)){
                /* avoid connecting the same rooms 2 times */
                if(i > 0){
                    if((room1 == list_room(graph[v1]) && room2 == list_room(graph[v2])) || (room2 == list_room(graph[v1]) && room1 == list_room(graph[v2])))
                        continue;
                }
                /* rooms to connect */
                room1 = list_room(graph[v1]);
                room2 = list_room(graph[v2]);
                /* positions in the array or NULL if not in the array */
                pos1 = in_list(list[room1], room2);
                pos2 = in_list(list[room2], room1);
                /* insert or update rooms */
                if(pos1 == NULL){
                    insert(&list[room1], room2, v, graph[v]);
                    insert(&list[room2], room1, v, graph[v]);
                }
                else{
                    if(pos1->cost > graph[v]){
                        pos1->cost = graph[v];
                        pos1->v = v;
                        pos2->cost = graph[v];
                        pos2->v = v;
                    }
                }
                
                
            } 
        }
    }
    /* free wall queue */
    free(queue);
    return list;
}
/**
 * @brief free the adjancency list
 * 
 * @param list list to free
 * @param rooms number of rooms of the list
 */
void free_list(_room **list, int rooms)
{
    _room *aux;
    /* free all list of the rooms */
    for(int i = 0; i < rooms; i++)
    {
        aux = list[i];
        while(list[i] != NULL){
            aux = list[i];
            list[i] = list[i]->next;
            free(aux);
        }
    }
    /* free array of lists */
    free(list);
}
