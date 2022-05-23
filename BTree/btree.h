#ifndef __BTREE_H__
#define __BTREE_H__

typedef void (*FuncionVisitante)(int dato);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

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
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit);

/**
 * : que retorne el número de nodos del árbol
 */
int btree_nodos(BTree arbol);

/**
 * : retorne 1 si el número dado se encuentra en el árbol, y 0 en caso contrario
 */

int btree_buscar(BTree arbol, int dato);

/**
 * retorna copia de un arbol
 */
BTree bree_copiar(BTree arbol);

/**
 * que retorne la altura del ´arbol
 */
int btree_altura(BTree arbol);

/**
 * retorna el número de nodos que se encuentran a la profundidad dada.
 */
int btree_nnodos_profundidad(BTree arbol, int lvlActual, int lvlDeseado);

/**
 * que retorne la profundidad del nodo que contiene el n´umero dado, y -1 si el
 * número no se encuentra en el ´arbol.
 */
int btree_profundidad(BTree arbol, int nro, int lvlActual);

/**
 * que retorne la suma total de los datos del ´arbol
 */
int btree_sumar(BTree arbol);



#endif /* __BTREE_H__ */

