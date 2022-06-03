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

//Compresion

void codificacionAuxArbol(BTree arbol, char** codificacion, struct ArrayWrapper arrWrapper, char char01){
    
    // Si es un nodo intermedio
    if (arbol->caracter == -1){
        // agrego un solo char
        arrWrapper.buf[strlen(arrWrapper.buf)] = char01;
        arrWrapper.buf[strlen(arrWrapper.buf) + 1] = '\0';
        // recursion
        codificacionAuxArbol(arbol->left, codificacion, arrWrapper, '0');
        codificacionAuxArbol(arbol->right, codificacion, arrWrapper, '1');
    }
    // Si es UNA hoja
    else{
        // agrego un solo char
        if(strlen(arrWrapper.buf) + 1 >= 100) { printf("Error: El tamaño buf es demasiado pequeño"); }
        else {
            arrWrapper.buf[strlen(arrWrapper.buf)] = char01;
            arrWrapper.buf[strlen(arrWrapper.buf) + 1] = '\0';
        }
        codificacion[arbol->caracter] = malloc(sizeof(char) * strlen(arrWrapper.buf) + 1);
        strcpy(codificacion[arbol->caracter], arrWrapper.buf);
        // Si ya terminó el camino hasta la hoja, le asigno su codificacion (buf)
    }
}

void codificacionArbol(BTree arbol, char** codificacion){
    struct ArrayWrapper arrWrapper;
    arrWrapper.buf[0] = '\0';  // lo inicializamos
    codificacionAuxArbol(arbol->left, codificacion, arrWrapper, '0');
    codificacionAuxArbol(arbol->right, codificacion, arrWrapper, '1');
}

//Obtiene la lista de las hojas ordenadas por peso, y retorna un unico arbol
BTree arbolHuffman(BTList lista){

    while ( lista->sig->sig != NULL){
        //Obtiene los dos primeros arboles de la lista
        BTree nodo1 = lista->arbol;
        BTree nodo2 = lista->sig->arbol;

        lista = lista->sig->sig;
        free(lista->ant->ant);
        free(lista->ant);
        lista->ant = NULL;
        //Los une como hijos de un nuevo nodo
        BTree nuevoNodo = btreeUnir(nodo1, nodo2);
        //Agrega el nuevo nodo cread en la lista (donde corresponda segun su peso)
        lista = btlistAgregar(lista, nuevoNodo);
    }

    //Caso especial para cuando en la lista solo quedan dos items
    BTree arbolFinal = btreeUnir(lista->arbol, lista->sig->arbol);
    free(lista->sig);
    free(lista);

    return arbolFinal;
}

//Retorna la serializacion binaria de la forma del arbol
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

//Retorna la serializacion de los caracteres del arbol recorriendo el arbol Inorder
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

// esto seria el texto comprimido en un archivo 
char* comprimirInput(char** codificacion, char* input, int *lenInput){
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

//Decompresion

// ======================  forma  ==============================

void parsear_aux_arbol(BTree arbol_ser, char* serializacion_forma, int* cont){
    if(*cont >= 512){
        printf("se pasa de 512 chars");
    }
    // printf("contador: %d\n", *cont);
    // es un nodo
    if (serializacion_forma[*cont] == '0'){
        arbol_ser->left = btreeCrear(-5, -5);   // !!!!!!!!
        arbol_ser->right = btreeCrear(-5, -5);   // !!!!!!!!
        *cont += 1;
        parsear_aux_arbol(arbol_ser->left, serializacion_forma, cont);
        *cont += 1;
        parsear_aux_arbol(arbol_ser->right, serializacion_forma, cont);
    }
    else if (serializacion_forma[*cont] != '1') {   // si el char no es 0 ni es 1
        printf("el archivo tiene un char que no es '0' ni '1', precisamente: %c", serializacion_forma[*cont]);
    }

}

// Rearma la forma del arbol desde su serialización (char* de bits)
BTree parsear_arbol(char* serializacion_forma_bin){

    BTree arbol_ser = btreeCrear(-5, -5);
    int* cont = malloc(sizeof(int));
    *cont = 0;

    parsear_aux_arbol(arbol_ser, serializacion_forma_bin, cont);

    return arbol_ser;
}

// ======================  hojas  ==============================

void parsear_hojas_rec(BTree arbol_forma, char* serializacion_hojas, int* cont){
    if(*cont >= 32){
        printf("se pasa de 256 chars");  //  ??????????????????????? 256 ??????????????????????????
    }
    // es nodo
    if (arbol_forma->left != NULL && arbol_forma->right != NULL){
        arbol_forma->caracter = (int)serializacion_hojas[*cont];     // almacenamos el char casteado a int
        *cont += 1;
        parsear_hojas_rec(arbol_forma->left, serializacion_hojas, cont);
        *cont += 1;
        parsear_hojas_rec(arbol_forma->right, serializacion_hojas, cont);
    }
    // es hoja
    else if (arbol_forma->left == NULL && arbol_forma->right == NULL){
        arbol_forma->caracter = (int)serializacion_hojas[*cont];     // almacenamos el char casteado a int
    }
}

BTree parsear_hojas(BTree arbol_forma, char* serializacion_hojas_chars){
    int* cont = malloc(sizeof(int));
    *cont = 0;
    parsear_hojas_rec(arbol_forma, serializacion_hojas_chars, cont);

    return arbol_forma;
}

//   ============================  compresión  ====================================
// con esta funcion voy a generar 2 archivos que almacenarán la compresión del texto 
// y la serialización de la forma y las hojas del arbol  

void compresion(char *path){

    int *lenInput = malloc(sizeof(int));
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
        BTree charTree = btreeCrear(index, frecuencias[index]);
        listaNodos = btlistAgregar(listaNodos, charTree);
    }

    BTree arbol = arbolHuffman(listaNodos);

    //Arreglo con los pares [caracter : codificación]
    char** codificacion = malloc(sizeof(char*) * 256);
    codificacionArbol(arbol, codificacion);

    //Serializacion
    char *serializacion = serializar(arbol);
    //Armo el nombre del archivo donde almacenaré la serialización
    char *serializacionPath = malloc(sizeof(char)*100);
    strcpy(serializacionPath, "");
    strcat(serializacionPath, path);
    strcat(serializacionPath, ".tree");
    //Escribo el archivo
    writefile(serializacionPath, serializacion, strlen(serializacion));

    //Comprimo el texto con la codificación y lo almaceno en compresión (como chars)
    char *compresion = comprimirInput(codificacion, buf, lenInput);
    //Armo el nombre del archivo donde almacenare la compresion
    char *compresionPath = malloc(sizeof(char)*100);
    strcpy(compresionPath, "");
    strcat(compresionPath, path);
    strcat(compresionPath, ".hf");
    //Escribo el archivo
    writefile(compresionPath, compresion, strlen(compresion));

    printf("Generados los archivos %s y %s\n", compresionPath, serializacionPath);
    free(compresionPath);
    free(serializacionPath);

}

//   ============================  descompresión  ====================================

void decompresion(char *path){
    int *lenSerializacion = malloc(sizeof(int));
    int *lenSerializacionBin = malloc(sizeof(int));

    char *serializacionPath = malloc(sizeof(char)*100);
    strcpy(serializacionPath, "");
    strcat(serializacionPath, path);
    strcat(serializacionPath, ".tree");   // por defecto este es el name del archivo q tiene la serialización

    // este texto esta en chars (a, b, c) y para la forma necesito transformarlo en bits (0 izq, 1 der)
    // so tomo solo los chars de la forma y lo exploto
    char* serializacion = readfile(serializacionPath, lenSerializacion);
    
    char* serializacion_forma_chars = malloc(sizeof(char) * 64);
    char* serializacion_hojas_chars = malloc(sizeof(char) * 256);


    for (int i = 0; i < 64; i++){   //    512/8 = 64
        serializacion_forma_chars[i] = serializacion[i];
    }

    char* serializacion_forma_bin = explode(serializacion_forma_chars, 64, lenSerializacionBin);
    
    
    for (int i = 0; i < 256; i++){   //    256/8 = 64
        serializacion_hojas_chars[i] = serializacion[i+64];
    }

    
    // probando
    

    BTree arbolForma = parsear_arbol(serializacion_forma_bin);
    
    btreeImprimir(arbolForma);

    BTree arbolFinal = parsear_hojas(arbolForma, serializacion_hojas_chars);
    
    //btreeImprimir(arbolFinal);


    btreeDestruir(arbolForma);
    btreeDestruir(arbolFinal); 
}


int main(int argc, char* argv[]){  // char* argv[]
    
    if(argc != 3){
        printf("Error en la cantidad de argumentos\n");
        return 0;
    }
    // Accion: 'C' para comprimir, 'D' para descomprimir
    if(strcmp(argv[1],"C") == 0){
        printf("C\n");
        compresion(argv[2]);
    }
    else if(strcmp(argv[1],"D") == 0){
        printf("D\n");
        decompresion(argv[2]);
    } 
    else {
        printf("Error en la accion a realizar\n");
        return 0;  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    

    return 0;
}
