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
