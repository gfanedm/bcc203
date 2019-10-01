
#ifndef REGISTRY_H_
#define REGISTRY_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "args.h"
#include "file.h"

using namespace std;

struct Registry {
  int key;
  long int data;
  char chars[500];
};

void generateRegisters(Arguments);
void exchange(Registry *, Registry *);
void shuffle(Registry *, int);

#endif
