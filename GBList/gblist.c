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