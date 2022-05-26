#include "gblist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


GBList gblist_agregar_inicio(GBList list, void *data, FuncionCopia copy) {
  GBNode *newNode = malloc(sizeof(GBNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->arbol = copy(data);
  return newNode;
}


GBList gblist_minimo(GBList list){
  GBList lista_aux = list;
  int minimo = lista_aux->arbol->peso;   // tomamos como valor mimino el primero

  while (lista_aux != NULL){
    if (minimo > lista_aux->arbol->peso){
      minimo = lista_aux->arbol->peso;
    }
    lista_aux = lista_aux->next;
  }
  return 
}
