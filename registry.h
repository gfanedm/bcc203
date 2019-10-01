
#ifndef REGISTRY_H
#define REGISTRY_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "args.h"
#include "file.h"

using namespace std;

struct Registry {
  long int key;
  long int data;
  char chars[500];
};

struct Index {
  int key;
  long int position;
};

void generateRegisters(Arguments);
void exchange(Registry *, Registry *);
void shuffle(Registry *, int);

#endif
