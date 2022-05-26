#include "btlist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

BTList btlist_agregar(BTList lista, BTree arbol) {
  BTList nuevoNodo = malloc(sizeof(BTNode));
  BTList index = lista;
  nuevoNodo->arbol = arbol;

  if( index == NULL ){                    //Caso lista vacia
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = NULL;
    return nuevoNodo;
  }
  
  while( index->sig != NULL && arbol->peso > index->data->peso){
    index = index->sig;
  }

  if( arbol->peso <= index->data->peso){  //Caso intermedio
    nuevoNodo->ant = index->ant;
    nuevoNodo->sig = index;
    index->ant->sig = nuevoNodo;
    index->ant = nuevoNodo;
  } else {                                //Caso ultimo nodo
    nuevoNodo->sig = NULL;
    nuevoNodo->ant = index;
    index->sig = nuevoNodo
  }

  return lista;
}


// ------------------------------- lo mio --------------------------------------------



BTList btlist_agregar_inicio(BTList list, BTree arbolAgregar) {
  BTNode *newNode = malloc(sizeof(BTNode));
  assert(newNode != NULL);
  newNode->sig = list;
  newNode->arbol = arbolAgregar;
  return newNode;
}


void btlist_eliminar_inicio(BTList list) {
  BTNode *nodeToDelete;
  if(list != NULL) {
    nodeToDelete = list;
    list = list->sig;
    free(nodeToDelete);
  }
}


BTree arbol_huffman(BTList lista){
  
  BTree nodo1;
  nodo1->caracter = lista->arbol->caracter;
  nodo1->peso = lista->arbol->peso;
  nodo1->left = lista->arbol->left;
  nodo1->right = lista->arbol->right;

  btlist_eliminar_inicio(lista);

  BTree nodo2;
  nodo2->caracter = lista->arbol->caracter;
  nodo2->peso = lista->arbol->peso;
  nodo2->left = lista->arbol->left;
  nodo2->right = lista->arbol->right;

  btlist_eliminar_inicio(lista);

  BTree NN = btree_unir(nodo1, nodo2);

  lista = btlist_agregar_inicio(lista, NN);

}
