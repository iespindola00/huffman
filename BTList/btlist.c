#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "btlist.h"

void btlist_imprimir(BTList lista){
  printf("Lista\n");
  if(lista != NULL){
    BTList index = lista;
    while( index != NULL){
      printf("Caracter: %c , Peso: %d\n", index->arbol->caracter, index->arbol->peso);
      index = index->sig;
    }
  }
}

BTList btlist_agregar(BTList lista, BTree arbol) {

  BTList nuevoNodo = malloc(sizeof(BTNode));
  BTList index = lista;
  nuevoNodo->arbol = arbol;

  if( index == NULL ){                    //Caso lista vacia
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = NULL;
    return nuevoNodo;
  }
  //Avanzo hasta la posicion en donde debo insertar ( o hasta el final de la lista )
  while( index->sig != NULL && arbol->peso >= index->arbol->peso){
    index = index->sig;
  }

  if( arbol->peso < index->arbol->peso ){  //Caso intermedio
    nuevoNodo->ant = index->ant;
    nuevoNodo->sig = index;
    index->ant->sig = nuevoNodo;
    index->ant = nuevoNodo;
  } else {                                //Caso ultimo nodo
    nuevoNodo->sig = NULL;
    nuevoNodo->ant = index;
    index->sig = nuevoNodo;
  }

  return lista;
}

void btlist_eliminar_inicio(BTList list) {
  BTNode *nodeToDelete;
  if(list != NULL) {
    nodeToDelete = list;
    list = list->sig;
    free(nodeToDelete);
  }
}
