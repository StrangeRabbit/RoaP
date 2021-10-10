#ifndef __TYPE_STRUCT__
#define __TYPE_STRUCT__

typedef enum {FALSE,TRUE} BOOL;

typedef struct
{
    int wall;
    int group;
    int sz;
} cell;

typedef enum {A1 = 1, A2, A3, A4, A5, A6} mode;

#endif