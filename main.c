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

BTree arbolHuffman(BTList lista){

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

char *serializarForma( BTree arbol ){
    char *buf = malloc(100000*sizeof(char));
    if(arbol->caracter == -1){
        strcat(buf, "0");
        strcat(buf, serializarForma(arbol->left));
        strcat(buf, serializarForma(arbol->right));
    } else {
        strcat(buf, "1");
    }

    return buf;
}

char *serializarHojas( BTree arbol ){
    char *buf = malloc(100000*sizeof(char));

    if(arbol->left != NULL){
        strcat(buf, serializarHojas(arbol->left));
    }

    if(arbol->caracter != -1){
        char hex[10];
        sprintf( hex, "%c", arbol->caracter);
        strcat(buf, hex);
    }

    if(arbol->right != NULL){
        strcat(buf, serializarHojas(arbol->right));
    }

    return buf;
}

char *serializar( BTree arbol ){
    //Creo un char puntero donde almacenaré la serializacion
    char *buf = malloc(sizeof(char)*1000);

    //Creo un int puntero en donde almacenar el largo de la serializacion de la forma.
    int *auxLen = malloc(sizeof(int));

    //Obtengo el binario de la serializacion de la forma
    char *serializacionFormaRaw = serializarForma(arbol);
    //Lo transformo en chars
    char *serializacionForma = implode(serializacionFormaRaw, strlen(serializacionFormaRaw), auxLen);

    //Obtengo la serializacion de las hojas (ya en chars)
    char *serializacionHojas = serializarHojas(arbol);

    //Guardo ambas partes en el buf a retornar
    strcat(buf, serializacionHojas);
    strcat(buf, serializacionForma);

    return buf;
}

char* comprimir(char** codificacion, char* input, int *lenInput){
    //Creo un int puntero en donde almacenar el largo de la serializacion de la forma.
    int *auxLen = malloc(sizeof(int));

    //Inicializo vacío un char puntero donde almaceno el binario de la compresion
    char *compresionRaw = malloc(sizeof(char)*10000);
    strcpy(compresionRaw, "");
    //Consumo caracter a caraacter del archivo de entrada y lo codifico
    for (int i = 0; i < *lenInput; i++){
        strcat(compresionRaw, codificacion[(unsigned char)input[i]]);
    }
    //Transformo el binario a chars
    char *compresion = malloc(sizeof(char)*1000);
    compresion = implode(compresionRaw, *lenInput, auxLen);
    return compresion;
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

    int *lenInput = malloc(sizeof(int));
    char *path = argv[2];
    char *buf = readfile(path, lenInput);

    //Inicializa arreglo con frecuencias
    int frecuencias[256];
    for(int index = 0; index < 256; index++){
        frecuencias[index] = 0;
    }

    //Calcula las frecuencias de cada caracter
    for(int pos = 0; pos < (*lenInput)-1; pos++){
        frecuencias[(int)buf[pos]]++;
    }

    //Genero un BTree para cada caracter, y lo agrego ordenenado segun su peso a una BTList
    BTList listaNodos = NULL;
    for(int index = 0; index < 256; index++){
        BTree charTree = btree_crear(index, frecuencias[index]);
        listaNodos = btlist_agregar(listaNodos, charTree);
    }

    BTree arbol = arbolHuffman(listaNodos);

    //Arreglo con los pares [caracter : codificación]
    char** codificacion = malloc(sizeof(char*) * 256);
    codificacion_arbol(arbol, codificacion);

    //Serializacion
    char *serializacion = serializar(arbol);
    //Armo el nombre del archivo donde almacenare la serializacion
    char *serializacionPath = malloc(sizeof(char)*100);
    strcat(serializacionPath, path);
    strcat(serializacionPath, ".tree");
    //Escribo el archivo
    writefile(serializacionPath, serializacion, strlen(serializacion));

    //Compresion
    char *compresion = comprimir(codificacion, buf, lenInput);
    //Armo el nombre del archivo donde almacenare la compresion
    char *compresionPath = malloc(sizeof(char)*100);
    strcat(compresionPath, path);
    strcat(compresionPath, ".hf");
    //Escribo el archivo
    writefile(compresionPath, compresion, strlen(compresion));

    printf("Generados los archivos %s y %s\n", compresionPath, serializacionPath);
    free(compresionPath);
    free(serializacionPath);
    return 0;
}
