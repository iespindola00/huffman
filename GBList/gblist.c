#include "gblist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>



GBList gblist_agregar_inicio(GBList list, BTree arbolAgregar) {
  GBNode *newNode = malloc(sizeof(GBNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->arbol = arbolAgregar;
  return newNode;
}


void gblist_eliminar_inicio(GBList list) {
  GBNode *nodeToDelete;
  if(list != NULL) {
    nodeToDelete = list;
    list = list->next;
    free(nodeToDelete);
  }
}


void arbol_huffman(GBList lista){
  for
  BTree nodo1;
  nodo1->caracter = lista->arbol->caracter;
  nodo1->peso = lista->arbol->peso;
  nodo1->left = lista->arbol->left;
  nodo1->right = lista->arbol->right;

  gblist_eliminar_inicio(lista);

  BTree nodo2;
  nodo2->caracter = lista->arbol->caracter;
  nodo2->peso = lista->arbol->peso;
  nodo2->left = lista->arbol->left;
  nodo2->right = lista->arbol->right;

  gblist_eliminar_inicio(lista);

  BTree NN = btree_unir(nodo1, nodo2);

  lista = gblist_agregar_inicio(lista, NN);

}