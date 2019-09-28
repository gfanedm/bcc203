/*
 * Args.h
 *
 *  Created on: 5 de set de 2019
 *      Author: thiago
 */

#ifndef ARGS_H_
#define ARGS_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct{
    int metodo;
    int quantidade;
    int situacao;
    int chave;
    bool mostra;
}args;
int valida_args(int argc, char *argv[], args *args);
#endif /* ARGS_H_ */
