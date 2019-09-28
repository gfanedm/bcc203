/*
 * Args.cpp
 *
 *  Created on: 5 de set de 2019
 *      Author: thiago
 */
#include "Args.h"
#include <iostream>
using namespace std;
int valida_args(int argc, char *argv[], args *args) {
	if (argc < 4 || argc > 6) {
		cout << "Argumentos incorretos. O modelo correto é:\n";
		cout << "<método> <quantidade> <situação> <chave> [-P]\n";
		return 0;
	}

	args->metodo = atoi(argv[1]);
	args->quantidade = atoi(argv[2]);
	args->situacao = atoi(argv[3]);
	args->chave = atoi(argv[4]);

	if (args->metodo < 1 || args->metodo > 4) {
		printf("Argumento <método> incorreto. Deve ser entre 1 e 4.\n");
		return 0;
	}

	if (args->situacao < 1 || args->situacao > 3) {
		printf("Argumento <situação> incorreto. Deve ser entre 1, 2 e 3.\n");
		return 0;
	}

	if (*argv[5] == 'P') {
		args->mostra = true;
	} else {
		args->mostra = false;
	}

	return 1;
}
