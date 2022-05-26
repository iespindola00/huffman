#ifndef __BTLIST_H__
#define __BTLIST_H__

#include "../BTree/btree.h"

typedef struct _BTNode {
  BTree arbol;
  struct _BTNode *ant;
  struct _BTNode *sig;
} BTNode;

typedef BTNode *BTList;

BTList btlist_agregar(BTList list, BTree arbol);

#endif /* __BTLIST_H__ */
