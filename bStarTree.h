#ifndef B_TREE_STAR_H
#define B_TREE_STAR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <iostream>

#include "registry.h"

using namespace std;

#define TAM 1000000
#define MMp 5
#define MM2 10

typedef struct Page* PointerPlus;

typedef enum { Intern, Extern } Type;

typedef struct Page {
  Type type;
  union {
    struct {
      int n;
      int key[MM2];
      PointerPlus pointer[MM2 + 1];
    } UnionIntern;
    struct {
      int n;
      Registry items[MM2];
      PointerPlus next;
    } UnionExtern;
  } Union;
} Page;

void initializeBStarTree(PointerPlus*);
bool searchBStarTree(Registry*, PointerPlus*, int&, int&);
void insertPageBStarTree(PointerPlus, Registry, PointerPlus, int&, int&);
void insBStarTree(Registry, PointerPlus, short*, Registry*, PointerPlus*, int&,
                  int&);
void insertBStarTree(Registry*, PointerPlus*, int&, int&);
void bTreeStar(FILE**, int, PointerPlus*, int&, int&);
void printBTreeStar(PointerPlus);
void star(int);

#endif
