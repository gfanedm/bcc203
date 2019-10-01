#ifndef ARGS_H_
#define ARGS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "string.h"

using namespace std;

struct Arguments {
  int method, quantity, situation, key;
  bool show;
};

int validateArguments(int, char *[], Arguments *);
#endif
