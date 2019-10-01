#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <cstdio>
#include <cstdlib>

#include "file.h"

struct BinData {
  int key;
  long data;
  char chars[500];
};

struct BinTree {
  int left;
  int right;
  BinData notch;
};

bool insertBinaryTree(BinTree, BinData, int, int, long*, long*);
bool searchBinaryTree(BinTree, BinData*, long*, long*);

#endif