/*
 * Acesso_sequencial.cpp
 *
 *  Created on: 29 de ago de 2019
 *      Author: thiago
 */
#define tam_pagina 4
#include "Acesso_sequencial.h"
indice *cria_indice(args args) {
	FILE *input = abre_arquivo_existente();
	reg temp;
	int tam_indice = (args.quantidade + tam_pagina - 1) / tam_pagina;
	indice *ind = new indice[tam_indice];
	for (int i = 0; i < tam_indice; i++) {
		ind[i].posicao = i;
		fread(&temp, sizeof(reg), 1, input);
		ind[i].chave = temp.chave;
		fseek(input, sizeof(reg) * (tam_pagina - 1), 1);
	}
	fclose(input);
	return ind;
}
bool pesquisa(long int pos, reg* registro, long int* comp, long int* transfer) {
	FILE *arq = abre_arquivo_existente();
	reg* pagina = new reg[tam_pagina];
	int qnt_reg = tam_pagina;
	if (pos == -1){
		fseek(arq, 0, SEEK_END);
		qnt_reg =  (ftell(arq)/sizeof(reg))%tam_pagina;
		*transfer +=2;
	}
    fseek(arq, pos * 4 * sizeof(reg), 0);
    fread(pagina, sizeof(reg), qnt_reg, arq);
    *transfer +=2;
    fclose(arq);
	for (int i = 0; i < qnt_reg; i++) {
		(*comp)++;
		if (pagina[i].chave == registro->chave) {
			*registro = pagina[i];
			return true;
		}
	}
	return false;
}

long int pesquisa_indice_sequencial(args args, long int* comp){
    int i = 0;
    long int pos;
    indice* ind = cria_indice(args);
    int tam_indice = (args.quantidade + tam_pagina - 1) / tam_pagina;
    (*comp)++;
    while (i < tam_indice && ind[i].chave <= args.chave) {
        pos = ind[i].posicao;
        (*comp)++;
        i++;
    }
	if (pos == tam_indice)
		pos = -1;
    return pos;
}
long int pesquisa_indice_binaria(indice *ind, int l, int *mid, int r, int x) {
    if (r >= l) {
        *mid = l + (r - l) / 2;
        /* Se o elemento for menor que o meio, então só pode
        estar à esquerda */
        if (ind[*mid].chave > x)
            return pesquisa_indice_binaria(ind, l, mid, *mid - 1, x);
        //Senão, só pode estar à direita
        return pesquisa_indice_binaria(ind, *mid + 1, mid, r, x);
    }
    /* Numa pesquisa binária comum, o retorno seria o índice de onde a chave foi
    encontrada, mas aqui é feito mid-1 para retornar o valor que vai ser usado
    como índice no índice */
    return ind[*mid-1].posicao;
}
