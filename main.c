#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "IO/io.h"
#include "BTree/btree.h"
#include "BTList/btlist.h"


void codificacion_aux_arbol(BTree arbol, char** codificacion, char buf[], char nro){
    
    // si es nodo
    if (arbol->caracter == -1){
        // agrego un solo char
        buf[strlen(buf)] = nro;
        printf("buf: %s \t", buf);
        codificacion_aux_arbol(arbol->left, codificacion, buf, '0');
        codificacion_aux_arbol(arbol->right, codificacion, buf, '1');
    }
    // si es hoja
    else{
        // agrego un solo char
        if(strlen(buf) + 1 >= 10000) { printf("error: el buf es demasiado pequeño"); }   
        else {
            buf[strlen(buf)] = nro;
            buf[strlen(buf) + 1] = '\0';
            //printf("buf: %s \t", buf);
        }
        codificacion[arbol->caracter] = malloc(sizeof(char) * strlen(buf) + 1);
        strcpy(codificacion[arbol->caracter], buf);   // si ya terminó el camino hasta la hoja, le asigno su codificacion (buf) / atoi me parsea el buf a int
        printf("codificación final: %s ", codificacion[arbol->caracter]);
    }
}

char** codificacion_arbol(BTree arbol){
    char** codificacion = malloc(sizeof(char*) * 256);
    char buf[10000] = "";
    codificacion_aux_arbol(arbol->left, codificacion, buf, '0');
    codificacion_aux_arbol(arbol->right, codificacion, buf, '1');
    printf("llegamos al final");

    return codificacion;
}


/*
char *comprimir_arbol( BTree arbol ){

    char *buf;
    if(arbol->caracter == -1){
        strcat(buf, "0");
        strcat(buf, comprimir_arbol(arbol->left));
        strcat(buf, comprimir_arbol(arbol->right));
    } else {
        strcat(buf, "1");
    }

    return buf;
}
*/
BTree arbol_huffman( BTList lista ){

    while ( lista->sig->sig != NULL){
        BTree nodo1 = lista->arbol;
        BTree nodo2 = lista->sig->arbol;

        lista = lista->sig->sig;
        free(lista->ant->ant);
        free(lista->ant);

        BTree nuevoNodo = btree_unir(nodo1, nodo2);

        lista = btlist_agregar(lista, nuevoNodo);
    }

    BTree arbol_final = btree_unir(lista->arbol, lista->sig->arbol);
    free(lista->sig);
    free(lista);

    return arbol_final;
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
    char *buf = readfile(argv[2], len);

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

    // creo arreglo para agregar los pares  char : codificación
    char** codificacion;
    codificacion = codificacion_arbol(arbol);

    for (int i = 0; i < 256; i++){
        printf("índice: %d codificación: %d", i, printf("codificación final: %s ", codificacion[i]));

    }
    
    


    return 0;
}
