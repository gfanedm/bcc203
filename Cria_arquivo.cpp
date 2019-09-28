/*
 * Cria_arquivo.cpp
 *
 *  Created on: 5 de set de 2019
 *      Author: thiago
 */




#include "Cria_arquivo.h"

FILE *abre_arquivo_existente(){
    FILE *input;
    if ((input = fopen("registros.bin", "r+b")) == NULL) {
        printf("Erro na abertura do arquivo de registros.\n");
        return NULL;
    } else {
        return input;
    }
}

FILE *cria_arquivo(){
    FILE *input;
    if ((input = fopen("registros.bin", "w+b")) == NULL) {
        printf("Erro na abertura do arquivo de registros.\n");
        return NULL;
    } else {
        return input;
    }
}
