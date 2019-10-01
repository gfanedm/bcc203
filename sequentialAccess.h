#ifndef SEQUENTIAL_ACCESS_H
#define SEQUENTIAL_ACCESS_H

#define MAX_TABLE 100
#define PAGE_SIZE 4

#include "registry.h"

Index* createIndex(Arguments);
bool search(long int, Registry*, long int*, long int*);

long int searchSequentialIndex(Arguments, long int*);
long int searchBinaryIndex(Index*, int, int*, int, int);

#endif
