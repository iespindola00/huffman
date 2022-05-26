#include "btree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/**
 * Crea una copia física del Arbol.
 */
BTree copyBTree(BTree arbol) {
  BTree copia = btree_crear();
  copia->peso = arbol->peso;
  copia->caracter = arbol->caracter;
  return copia;
}

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { return NULL; }

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
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->caracter = -1;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  nuevoNodo->peso = left->peso + right->peso;
  return nuevoNodo;
}  

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
FuncionVisitante visit) {
  BTree nodo = arbol;
  // recorrido preorden
  if(orden == BTREE_RECORRIDO_PRE){
    if (btree_empty(nodo)){
      return;
    }

    visit(nodo->caracter);  // mostrar

    btree_recorrer(nodo->left, orden, visit);

    btree_recorrer(nodo->right, orden, visit);
  }
  
  // recorrido inorden
  if(orden == BTREE_RECORRIDO_IN){
    if (btree_empty(nodo)){
      return;
    }

    btree_recorrer(nodo->left, orden, visit);

    visit(nodo->caracter);  // mostrar

    btree_recorrer(nodo->right, orden, visit);
  }

  // recorrido postorden
  if(orden == BTREE_RECORRIDO_POST){
    if (btree_empty(nodo)){
      return;
    }

    btree_recorrer(nodo->left, orden, visit);

    btree_recorrer(nodo->right, orden, visit);

    visit(nodo->caracter);  // mostrar
  }
  
  return;
}

// ej 3
/*
//a 
int btree_nodos(BTree arbol){
  int cantN = 1;
  BTree nodo = arbol;
  
  if (nodo->left != NULL){
    cantN += btree_nodos(nodo->left);
  }
  
  if (nodo->right != NULL){
    cantN += btree_nodos(nodo->right);
  }
  return cantN;
}
*/

//b
int btree_buscar(BTree arbol, int caracter){
  printf("\nel arbol->caracter es: %d y el caracter es %d\n", arbol->caracter, caracter);
  printf("%d", arbol->caracter == caracter);
  if(btree_empty(arbol)) return 0;
  if(arbol->caracter == caracter){
    printf("entroooooo");
    return 1;
  }
  if (!btree_empty(arbol->left)){
    btree_buscar(arbol->left, caracter);
  }
  if (!btree_empty(arbol->right)){
    btree_buscar(arbol->right, caracter);
  }
  // si estuviese ordenado
  /*
  else if(arbol->caracter > caracter){
    return btree_buscar(arbol->left, caracter);
  }
  else if(arbol->caracter < caracter){
    return btree_buscar(arbol->right, caracter);
  }
  */
  return 0;
}

int max(int a, int b){
  return a > b ? a : b;
}

int btree_altura(BTree arbol){
  if (btree_empty(arbol)){
    return -1;
  }
  // una hoja
  else if(btree_empty(arbol->left) && btree_empty(arbol->right)){
    return 0;
  }
  
  int altura = 1 + max( btree_altura(arbol->left), btree_altura(arbol->right) );
  return altura;
}

int btree_nnodos_profundidad(BTree arbol, int lvlActual, int lvlDeseado){
  if (btree_empty(arbol)){
    return 0;
  }
  // esto cumple 2ble funcion, si es el lvl 0 el q queremos, nos devuelve 1 (el único nodo), 
  // else nos sirve para la recursion
  if (lvlActual == lvlDeseado) return 1;
  
  return 
  btree_nnodos_profundidad(arbol->left, lvlActual+1, lvlDeseado) + 
  btree_nnodos_profundidad(arbol->right, lvlActual+1, lvlDeseado);
}

/*
int btree_profundidad(BTree arbol, int nro, int lvlActual){
  if (btree_empty(arbol)){
    return -1;
  }
  if (arbol->caracter == nro){
    return lvlActual;
  }
  
  int lvl = btree_profundidad(arbol->left, nro, lvlActual+1);
  if (lvl != -1){
    return lvl;
  }
  
  lvl = btree_profundidad(arbol->right, nro, lvlActual+1);

  return lvl;
}
*/

int btree_sumar(BTree arbol){ 
  if (btree_empty(arbol)){  // si vacio
    return -1;
  }
  int suma =  arbol->caracter;
  
  if(!btree_empty(arbol->left))
    suma += btree_sumar(arbol->left); 
  if (!btree_empty(arbol->right))
    suma += btree_sumar(arbol->right); 
  
  return suma;
}
