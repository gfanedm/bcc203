/*
 * Registro.cpp
 *
 *  Created on: 5 de set de 2019
 *      Author: thiago
 */
#include "Registro.h"

void troca(reg *a, reg *b) {
	reg temp = *a;
	*a = *b;
	*b = temp;
}

void shuffle(reg *registros, int n) {
	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		troca(&registros[i], &registros[j]);
	}
}

void gera_registros(args args) {
	reg *registros;
	registros = new reg[args.quantidade];
	if (args.situacao == 1 || args.situacao == 3) {
		for (int i = 0; i < args.quantidade; ++i) {
			registros[i].chave = i;
			registros[i].dado1 = rand();
			for (int j = 0; j < 500; ++j) {
				registros[i].dado2[j] = (rand() % 95) + 32;
			}
		}
		if (args.situacao == 3) {
			shuffle(registros, args.quantidade);
		}

	} else if (args.situacao == 2) {
		for (int i = args.quantidade - 1; i >= 0; --i) {
			registros[i].chave = i;
			registros[i].dado1 = rand();
			for (int j = 0; j < 500; ++j) {
				registros[i].dado2[j] = (rand() % 95) + 32;
			}
		}
	}
	 FILE* output = cria_arquivo();
	 for (int k = 0; k < args.quantidade; ++k) {
	 fwrite(&registros[k], sizeof(reg), 1, output);
	 }
	 free(registros);
	 fclose(output);
	return;
}
