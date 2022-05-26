#ifndef __BTLIST_H__
#define __BTLIST_H__

#include "btree.h"

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef int (*Predicado) (void *dato);

typedef struct _BTNode {
  BTree arbol;
  struct _BTNode *ant;
  struct _BTNode *sig;
} BTNode;

typedef BTNode *BTList;

BTList btlist_agregar(BTList list, BTree arbol);

#endif /* __BTLIST_H__ */
