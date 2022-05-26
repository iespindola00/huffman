#include "glist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Devuelve una lista vac�a.
 */
GList glist_crear() { return NULL; }

/**
 * Destruccion de la lista.
 * destroy es una funci�n que libera el dato almacenado.
 */
void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}

/**
 * Determina si la lista es vac�a.
 */
int glist_vacia(GList list) { return (list == NULL); }

/**
 * Agrega un elemento al inicio de la lista.
 * copy es una funci�n que retorna una copia f�sica del dato.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

GList glist_filtrar(GList lista, FuncionCopia c, Predicado p){
  GList nuevaLista = glist_crear();
  for (GNode *node = lista; node != NULL; node = node->next){
    if(p(node->data)){
      nuevaLista = glist_agregar_inicio(nuevaLista, node->data, c);
    }
  }
  return nuevaLista;
}

GList glist_minimo(GList arbol){
  
}
