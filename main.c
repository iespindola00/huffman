#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("Error en la cantidad de argumentos\n");
        return 0;
    }

    if(strcmp(argv[1],"C") && strcmp(argv[1],"D")){
        printf("Error en la accion a realizar\n");
        return 0;
    }

    printf("Listo\n");

    return 0;
}
