#pragma once

#include<cstdio>
#include<cstdlib>

struct BinData;
struct BinTree;

bool insertBinaryTree(FILE*, BinTree, BinData, int, int, long*, long*);
bool searchBinaryTree(FILE*, BinTree, BinData*, long*, long*);
