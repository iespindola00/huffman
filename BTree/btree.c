#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "btree.h"

int max(int a, int b){
  return a > b ? a : b;
}

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear( int caracter, int peso ){
  BTree nuevoTree = malloc(sizeof(BTNodo));
  nuevoTree->caracter = caracter;
  nuevoTree->peso = peso;
  nuevoTree->left = NULL;
  nuevoTree->right = NULL;
  return nuevoTree;
}

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
  BTree nuevoNodo = malloc(sizeof(BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->caracter = -1;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  nuevoNodo->peso = left->peso + right->peso;
  return nuevoNodo;
}  
