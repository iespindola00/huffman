#ifndef __GBLIST_H__
#define __GBLIST_H__

#include "btree.h"

// lista de nodos(tree)

typedef struct _GBNode {
  BTree arbol;
  struct _GBNode *next;
} GBNode;

typedef GBNode *GBList;

typedef void (*FuncionDestructora)(BTree dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef int (*Predicado) (void *dato);

/**
 * agrega un elemento al inicio 
 */
void gblist_agregar_inicio(GBList list);

void gblist_eliminar_inicio(GBList list);


#endif /* __GBLIST_H__ */