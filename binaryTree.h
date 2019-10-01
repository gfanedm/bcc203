#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "file.h"
#include "registry.h"

using namespace std;

struct BinTree {
  int left;
  int right;
  Registry notch;
};

bool insertBinaryTree(BinTree, Registry, int, int, long*, long*);
bool searchBinaryTree(BinTree, Registry*, long*, long*);

#endif