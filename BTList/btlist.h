#ifndef __BTLIST_H__
#define __BTLIST_H__

#include "../BTree/btree.h"

typedef struct _BTNode {
  BTree arbol;
  struct _BTNode *ant;
  struct _BTNode *sig;
} BTNode;

typedef BTNode *BTList;

/**
 * Recorre la lista imprimiendo caracter y peso
 */
void btlist_imprimir(BTList lista);

/**
 * Agrega un elemento al inicio
 */
BTList btlist_agregar(BTList list, BTree arbol);

/**
 * Elimina el primer elem de la lsita
 */
void btlist_eliminar_inicio(BTList list);

#endif /* __BTLIST_H__ */
