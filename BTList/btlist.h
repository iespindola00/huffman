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
 * agrega un elemento al inicio
 */
BTList btlist_agregar_inicio(BTList list, BTree arbolAgregar);

/**
 * elimina el primer elem de la lsita
 */
void btlist_eliminar_inicio(BTList list);

/**
 * agrega un elemento al inicio
 */
BTList btlist_agregar(BTList list, BTree arbol);

/**
 * retorna el arbol de huffman
 */
BTree arbol_huffman(BTList lista);

#endif /* __BTLIST_H__ */
