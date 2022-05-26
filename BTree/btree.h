#ifndef __BTREE_H__
#define __BTREE_H__

typedef void (*FuncionVisitante)(int dato);

struct _BTNodo {
  int caracter;
  int peso;
  struct _BTNodo *left;
  struct _BTNodo *right;
};

typedef struct _BTNodo *BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);
 
/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(BTree left, BTree right);

/**
 * que retorne la suma total de los datos del ´arbol
 */
int btree_sumar(BTree arbol);

#endif /* __BTREE_H__ */
