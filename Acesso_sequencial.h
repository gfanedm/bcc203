/*
 * acesso_sequencial.h
 *
 *  Created on: 29 de ago de 2019
 *      Author: thiago
 */
#ifndef ACESSO_SEQUENCIAL_H_
#define ACESSO_SEQUENCIAL_H_
#define MAXTABELA 100
#include "Registro.h"

typedef struct{
	int chave;
	long int posicao;
}indice;
indice *cria_indice(args args);
bool pesquisa(long int pos, reg* registro, long int* comp, long int* transfer);
long int pesquisa_indice_sequencial(args args, long int* comp);
long int pesquisa_indice_binaria(indice *ind, int l, int *mid, int r, int x);
#endif
