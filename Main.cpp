/*
 * Main.cpp
 *
 *  Created on: 5 de set de 2019
 *      Author: thiago
 *
 Execução do programa: <metodo> <quantidade> <situacao> <chave> [-P]
 <metodo>:		1 à 4, de acordo com os metodos implementados;
 <quantidade>:	quantidade de registros no arquivo;
 <situacao>:		1 (ordenado ascendente); 2 (ordenado descendente); 3 (desordenado aleartóriamente);
 <chave>:		Chave a ser pesquisada;
 [-P]:			Argumento opcional, representa que as chaves de pesquisa dos registros do arquivo apareçam na tela;
 Métodos:
 - Pesquisa sequencial:	1
 - Pesquisa binária:		2
 - Árvore B:				3
 - Árvore B*:			4
 Situação:
 - ORDENADO CRESCENTE:		1
 - ORDENADO DECRESCENTE:		2
 - ALEARTÒRIO:				3
 */

#include "Registro.h"
#include "Acesso_sequencial.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
	args args;
	if (valida_args(argc, argv, &args) == 0)
		return 0;
	else
		gera_registros(args);

	if (args.metodo == 1) {

		// declaracao de variaveis
		clock_t t1, t2;
		reg aux;
		long int comp = 0;
		long int transfer = 0;

		t1 = clock();

		long int pos = pesquisa_indice_sequencial(args, &comp);
		aux.chave = args.chave;
		bool resultado = pesquisa(pos, &aux, &comp, &transfer);
		t2 = clock() - t1;
		if (resultado == true) cout << "Chave encontrada: " << aux.chave << endl; // valida a busca
		else cout << "Chave não foi encontrada" << endl;

		cout << "Tempo de pesquisa sequencial: " << (((float)t2)/CLOCKS_PER_SEC) << endl;
		cout << "Numero de comparacoes: " << comp << endl;
		cout << "Numero de transferencias: " << transfer;
	} else {


		if (args.metodo == 2) {

		} else {
			if (args.metodo == 3) {

			} else {
			}
		}
		return 0;
	}
}
