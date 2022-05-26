#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "btree.h"

int max(int a, int b){
  return a > b ? a : b;
}

/**
 * Crea una copia física del Arbol.
 */
BTree copyBTree(BTree arbol) {
  BTree copia = btree_crear();
  copia->peso = arbol->peso;
  copia->caracter = arbol->caracter;
  return copia;
}

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { return NULL; }

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) { return nodo == NULL; }

/**
 * Crea un nuevo arbol, con el caracter dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->caracter = -1;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  nuevoNodo->peso = left->peso + right->peso;
  return nuevoNodo;
}  

int btree_sumar(BTree arbol){ 
  if (btree_empty(arbol)){  // si vacio
    return -1;
  }
  int suma =  arbol->caracter;
  
  if(!btree_empty(arbol->left))
    suma += btree_sumar(arbol->left); 
  if (!btree_empty(arbol->right))
    suma += btree_sumar(arbol->right); 
  
  return suma;
}
