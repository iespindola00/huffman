#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "IO/io.h"
#include "BTree/btree.h"
#include "BTList/btlist.h"

struct ArrayWrapper
{
    char buf[100];
};


// NOTA: NRO es un caracter "1" || "0"
void codificacion_aux_arbol(BTree arbol, char** codificacion, struct ArrayWrapper arrWrapper, char nro){
    
    // si es nodo
    if (arbol->caracter == -1){
        // agrego un solo char
        arrWrapper.buf[strlen(arrWrapper.buf)] = nro;
        arrWrapper.buf[strlen(arrWrapper.buf) + 1] = '\0';
        // recursion
        codificacion_aux_arbol(arbol->left, codificacion, arrWrapper, '0');
        codificacion_aux_arbol(arbol->right, codificacion, arrWrapper, '1');
    }
    // si es hoja
    else{
        // agrego un solo char
        if(strlen(arrWrapper.buf) + 1 >= 100) { printf("error: el buf es demasiado pequeño"); }
        else {
            arrWrapper.buf[strlen(arrWrapper.buf)] = nro;
            arrWrapper.buf[strlen(arrWrapper.buf) + 1] = '\0';
        }
        codificacion[arbol->caracter] = malloc(sizeof(char) * strlen(arrWrapper.buf) + 1);
        strcpy(codificacion[arbol->caracter], arrWrapper.buf);   // si ya terminó el camino hasta la hoja, le asigno su codificacion (buf) / atoi me parsea el buf a int
    }
}

void codificacion_arbol(BTree arbol, char** codificacion){
    struct ArrayWrapper arrWrapper;
    arrWrapper.buf[0] = '\0';  // lo inicializamos
    codificacion_aux_arbol(arbol->left, codificacion, arrWrapper, '0');
    codificacion_aux_arbol(arbol->right, codificacion, arrWrapper, '1');
}

char *comprimir_arbol( BTree arbol ){

    char *buf = malloc(100000*sizeof(char));
    if(arbol->caracter == -1){
        strcat(buf, "0");
        strcat(buf, comprimir_arbol(arbol->left));
        strcat(buf, comprimir_arbol(arbol->right));
    } else {
        strcat(buf, "1");
    }

    return buf;
}

BTree arbol_huffman(BTList lista){

    while ( lista->sig->sig != NULL){
        BTree nodo1 = lista->arbol;
        BTree nodo2 = lista->sig->arbol;

        lista = lista->sig->sig;
        free(lista->ant->ant);
        free(lista->ant);
        lista->ant = NULL;
        BTree nuevoNodo = btree_unir(nodo1, nodo2);
        lista = btlist_agregar(lista, nuevoNodo);
    }

    BTree arbol_final = btree_unir(lista->arbol, lista->sig->arbol);
    free(lista->sig);
    free(lista);

    return arbol_final;
}

char* compresion(char** codificacion, char* texto, int* len){
    char* codificacion_final = malloc(sizeof(char)*100000);
    for (int i = 0; i < *len; ++i){
        strcat(codificacion_final, codificacion[(unsigned char)texto[i]]);
    }
    return codificacion_final;
}

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("Error en la cantidad de argumentos\n");
        return 0;
    }

    // Accion: 'C' para comprimir, 'D' para descomprimir
    if(strcmp(argv[1],"C") && strcmp(argv[1],"D")){
        printf("Error en la accion a realizar\n");
        return 0;
    }

    int *len = malloc(sizeof(int));
    char *path = argv[2];
    char *buf = readfile(path, len);

    //Inicializa arreglo con frecuencias
    int frecuencias[256];
    for(int index = 0; index < 256; index++){
        frecuencias[index] = 0;
    }

    //Calcula las frecuencias de cada caracter
    for(int pos = 0; pos < (*len)-1; pos++){
        frecuencias[(int)buf[pos]]++;
    }

    //Genero un BTree para cada caracter, y lo agrego ordenenado segun su peso a una BTList
    BTList listaNodos = NULL;
    for(int index = 0; index < 256; index++){
        BTree charTree = btree_crear(index, frecuencias[index]);
        listaNodos = btlist_agregar(listaNodos, charTree);
    }

    BTree arbol = arbol_huffman(listaNodos);

    //Arreglo para agregar los pares [char : codificación]
    char** codificacion = malloc(sizeof(char*) * 256);
    codificacion_arbol(arbol, codificacion);

    int *newLenSerializacion = malloc(sizeof(int));
    char *hexa_arbol = implode(comprimir_arbol(arbol), *len, newLenSerializacion);

    char *treePath = malloc(sizeof(char)*100);
    treePath = strcat(treePath, path);
    treePath = strcat(treePath, ".tree");
    writefile(treePath, hexa_arbol, *newLenSerializacion);

    int *newLen = malloc(sizeof(int));
    char *hexa = implode(compresion(codificacion, buf, len), *len, newLen);
    writefile(strcat(path, ".hf"), hexa, *newLen);
    return 0;
}
