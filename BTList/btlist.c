#include "btlist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

BTList btlist_agregar(BTList lista, BTree arbol, FuncionCopia copia) {
  BTList nuevoNodo = malloc(sizeof(BTNode));
  BTList index = lista;
  nuevoNodo->arbol = copia(arbol);

  if( index == NULL ){
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = NULL;
    return nuevoNodo
  }
  while( index != NULL ){
    if( arbol->peso <= index->data->peso){
      nuevoNodo->ant = index->ant;
      nuevoNodo->sig = index;
      index->ant->sig = nuevoNodo;
      index->ant = nuevoNodo;
      return lista;
    }
    index = index->sig;
  }

  return lista;
}
