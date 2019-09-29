#pragma once

#include <cstdio>
#include <cstdlib>
#include "Cria_arquivo.h"

struct BinData
{
	int key;
	long data;
    char chars[501];
};

struct BinTree
{
	int left;
	int right;
	BinData notch;
};

bool insertBinaryTree(BinTree, BinData, int, int, long*, long*);
bool searchBinaryTree(BinTree, BinData*, long*, long*);
