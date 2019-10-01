#ifndef ACESSO_SEQUENCIAL_H_
#define ACESSO_SEQUENCIAL_H_

#define MAX_TABLE 100
#define PAGE_SIZE 4

#include "registry.h"

struct Index {
  int key;
  long int position;
};

Index* createIndex(Arguments);
bool search(long int, Registry*, long int*, long int*);

long int searchSequentialIndex(Arguments, long int*);
long int searchBinaryIndex(Index*, int, int*, int, int);

#endif
