#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"
#include "lib.h"

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

int list_room(int room)
{
    return room * (-1) - 2;
}

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

_room *in_list(_room *list, int v)
{
    while(list != NULL)
    {
        if(list->room == v) return list;
        list = list->next;
    }
    return NULL;
}

_room **create_list(int *graph, int rooms, edge *head, edge *tail, int L, int C)
{
    int i, v, v1, v2, room1, room2;
    _room *pos1, *pos2;

    _room **list = (_room**) malloc(rooms * sizeof(_room*));
    for(i = 0; i < rooms; i++)
        list[i] = NULL;
    
    while (head != NULL)
    {
        v = BFS_pop(&head, &tail);
        
        v1 = v - 1;
        v2 = v + 1;
        
        room1 = 0;
        room2 = 0;

        for(i = 0; i < 2; i++, v1 = v - C, v2 = v + C){
            if(LIST_connectable(graph, v1, v2, L, C)){
                if(i > 0){
                    if((room1 == list_room(graph[v1]) && room2 == list_room(graph[v2])) || (room2 == list_room(graph[v1]) && room1 == list_room(graph[v2])))
                        continue;
                }
                room1 = list_room(graph[v1]);
                room2 = list_room(graph[v2]);
                
                pos1 = in_list(list[room1], room2);
                pos2 = in_list(list[room2], room1);

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
    return list;
}

void free_list(_room **list, int rooms)
{
    _room *aux;
    for(int i = 0; i < rooms; i++)
    {
        aux = list[i];
        while(list[i] != NULL){
            aux = list[i];
            list[i] = list[i]->next;
            free(aux);
        }
    }
    free(list);
}
