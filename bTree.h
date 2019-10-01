#ifndef B_TREE_H
#define B_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <iostream>

#include "registry.h"

#define M 20
#define MM 2 * M
#define SIZE 1000

using namespace std;

struct Page;
typedef struct Page* Pointer;

void initialize(Pointer&);
bool searchBTree(Registry*, Pointer, int&);
void insertOnPage(Pointer, Registry, Pointer, int&);
void insertRegistry(Registry, Pointer, short*, Registry*, Pointer*, int&);
void insert(Registry, Pointer*, int&);
void bTree(int);

#endif