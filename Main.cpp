/*
 * Main.cpp
 *
 *  Created on: 5 de set de 2019
 *      Author: thiago
 *
 Execucao do programa: <metodo> <quantidade> <situacao> <chave> [-P]
 <metodo>:		1 a 4, de acordo com os metodos implementados;
 <quantidade>:	quantidade de registros no arquivo;
 <situacao>:		1 (ordenado ascendente); 2 (ordenado descendente); 3
 (desordenado aleartoriamente); <chave>:		Chave a ser pesquisada;
 [-P]:			Argumento opcional, representa que as chaves de pesquisa
 dos registros do arquivo aparecam na tela; Metodos:
 - Pesquisa sequencial:	1
 - Pesquisa binnria:		2
 - Arvore B:				3
 - Arvore B*:			4
 Situacao:
 - ORDENADO CRESCENTE:		1
 - ORDENADO DECRESCENTE:		2
 - ALEARTORIO:				3
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

#include "bStarTree.h"
#include "bTree.h"
#include "binaryTree.h"
#include "file.h"
#include "registry.h"
#include "sequentialAccess.h"

using namespace std;

int main(int argc, char* argv[]) {
  Arguments args;

  if (validateArguments(argc, argv, &args) == 0) {
    return 0;
  } else {
    generateRegisters(args);
  }

  if (args.method == 1) {
    cout << "Metodo de pesquisa sequencial." << endl;
    clock_t t1, t2;

    Registry aux;
    long int comp = 0;
    long int transfer = 0;

    t1 = clock();

    long int pos = searchSequentialIndex(args, &comp);
    aux.key = args.key;

    bool result = search(pos, &aux, &comp, &transfer);
    t2 = clock() - t1;

    if (result) {
      cout << "Chave encontrada: " << aux.key << endl;
    } else {
      cout << "Chave nao foi encontrada" << endl;
    }

    cout << "Tempo de pesquisa sequencial: " << (((float)t2) / CLOCKS_PER_SEC)
         << endl;
    cout << "Numero de comparacoes: " << comp << endl;
    cout << "Numero de transferencias: " << transfer;

  } else if (args.method == 2) {
    cout << "Metodo de pesquisa Arvore binaria. " << endl;
    FILE* file = openFile();
    clock_t start1 = clock(), last1, start2, last2;

    long int comp = 0, transf = 0;

    Registry data;
    BinTree registry;

    transf++;

    fread(&data, sizeof(Registry), 1, file);

    registry.notch = data;
    registry.left = -1;
    registry.right = -1;

    FILE* tree = openBin();

    int cont = 1;
    fwrite(&registry, sizeof(BinTree), 1, tree);
    while (fread(&data, sizeof(Registry), 1, file) == 1) {
      transf++;
      insertBinaryTree(tree, registry, data, cont, args.situation, &transf,
                       &comp);
      cont++;
    }

    last1 = clock();
    start2 = clock();

    data.key = args.key;

    rewind(tree);
    bool find = searchBinaryTree(tree, registry, &data, &transf, &comp);

    last2 = clock();

    if (find)
      cout << "Chave encontrada: " << data.key << endl;
    else
      cout << "Chave nao foi encontrada" << endl;

    cout << "Tempo de insercao binaria: "
         << (((float)(last1 - start1)) / CLOCKS_PER_SEC) << endl;
    cout << "Tempo de pesquisa binaria: "
         << (((float)(last2 - start2)) / CLOCKS_PER_SEC) << endl;
    cout << "Numero de comparacoes: " << comp << endl;
    cout << "Numero de transferencias: " << transf << endl;

  } else if (args.method == 3) {
    cout << "Metodo de pesquisa Arvore B " << endl;
    bTree(args.key);

  } else if (args.method == 4) {
    cout << "Metodo de pesquisa Arvore B* " << endl;
    star(args.key);

  } else {
    cout << "Metodo nao encontrado." << endl;
  }
  exit(0);
  return 0;
}
