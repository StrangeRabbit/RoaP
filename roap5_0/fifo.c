#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#include "fifo.h"

typedef struct _element
{
      Item item;
      struct _element *next;
} element;

struct fila
{
      element *primeiro;
      element *ultimo;
};

element *FilaNew(Item vItem, element *pNext)
{
      element *x = (element *)malloc(sizeof(element));
      x->item = vItem;
      x->next = pNext;
      return x;
}

F *FilaInit()
{
      F *pFila = (F *)malloc(sizeof(F));
      pFila->primeiro = pFila->ultimo = NULL;
      return pFila;
}

void FilaPut(F *pFila, Item vI)
{
      if (pFila->primeiro == NULL)
      { /* a fila está vazia */
            pFila->ultimo = FilaNew(vI, pFila->primeiro);
            pFila->primeiro = pFila->ultimo;
            return;
      }
      /* o item é colocado no fim da lista */
      pFila->ultimo->next = FilaNew(vI, NULL);
      pFila->ultimo = pFila->ultimo->next;
}

int FilaEmpty(F *pFila)
{
      if (pFila->ultimo != NULL)
            return 1;
      return 0;
}

Item FilaGet(F *pFila)
{
      Item item = pFila->primeiro->item;
      element *elem = pFila->primeiro->next;
      free(pFila->primeiro);
      pFila->primeiro = elem;
      return item;
}
