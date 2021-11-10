#ifndef FIFO
#define FIFO

#include "Item.h"

typedef struct fila F;
//void FilaDump(F *);
F *FilaInit();
int FilaEmpty(F *);
void FilaPut(F *, Item);
Item FilaGet(F *);

#endif