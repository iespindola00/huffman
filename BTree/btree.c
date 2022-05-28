#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "btree.h"

BTree btree_crear( int caracter, int peso ){
  BTree nuevoTree = malloc(sizeof(BTNodo));
  nuevoTree->caracter = caracter;
  nuevoTree->peso = peso;
  nuevoTree->left = NULL;
  nuevoTree->right = NULL;
  return nuevoTree;
}

void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

int btree_empty(BTree nodo) { return nodo == NULL; }

BTree btree_unir(BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->caracter = -1;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  nuevoNodo->peso = left->peso + right->peso;
  return nuevoNodo;
}  

void btree_imprimir(BTree arbol){
  if(arbol->caracter == -1){
    //printf("Left\n");
    btree_imprimir(arbol->left);
    //printf("Right\n");
    btree_imprimir(arbol->right);
  } else {
    printf("%d\n", arbol->caracter);
  }
}
