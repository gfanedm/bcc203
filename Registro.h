
#ifndef REGISTRO_H_
#define REGISTRO_H_

#include "Args.h"
#include "Cria_arquivo.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

typedef struct Registro{
    int chave;
    long int dado1;
    char dado2[500];
}reg;

void gera_registros(args args);
void troca(reg *a, reg *b);
void shuffle(reg *registros, int n);

#endif /* REGISTRO_H_ */
