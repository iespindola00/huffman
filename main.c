#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "IO/io.h"
#include "glist.h"
#include "btree.h"

// q hay en argv[0] ??
int main(int argc, char *argv[]){

    if(argc != 3){
        printf("Error en la cantidad de argumentos\n");
        return 0;
    }

    // la acción tiene q ser comprimir o descomprimir
    if(strcmp(argv[1],"C") && strcmp(argv[1],"D")){
        printf("Error en la accion a realizar\n");
        return 0;
    }

    int *len = malloc(sizeof(int));
    char *buf = readfile(argv[2], len);

    //Inicializar arreglo con frecuencias
    int frecuencias[256];
    for(int index = 0; index < 256; index++){
        frecuencias[index] = 0;
    }

    //Calcular las frecuencias de cada caracter
    for(int pos = 0; pos < (*len)-1; pos++){
        frecuencias[(int)buf[pos]]++;
    }

    GList listaNodos = glist_crear();

    for(int index = 0; index < 256; index++){
        BTree charTree = btree_crear();
        charTree->caracter = index;
        charTree->peso = frecuencias[index];
        glist_agregar_inicio(listaNodos, charTree, copyBTree);
    }

    return 0;
}
