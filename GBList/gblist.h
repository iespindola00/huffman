#ifndef __GBLIST_H__
#define __GBLIST_H__

#include "btree.h"

// lista de nodos(tree)

typedef struct _GBNode {
  BTree arbol;
  struct _GBNode *next;
} GBNode;

typedef GBNode *GBList;

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef int (*Predicado) (void *dato);

GBList gblist_agregar_inicio(GBList list, void *data, FuncionCopia copy);

// me devuelve el char con la menor frecuencia de una lista de arboles
int gblist_minimo(GBList list);

#endif /* __GBLIST_H__ */