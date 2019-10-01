#include "registry.h"

void exchange(Registry *a, Registry *b) {
  Registry temp = *a;
  *a = *b;
  *b = temp;
}

void shuffle(Registry *registry, int n) {
  for (int i = n - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    exchange(&registry[i], &registry[j]);
  }
}

void generateRegisters(Arguments args) {
  Registry *registry = new Registry[args.quantity];
  if (args.situation == 1 || args.situation == 3) {
    for (int i = 0; i < args.quantity; ++i) {
      registry[i].key = i;
      registry[i].data = rand();

      for (int j = 0; j < 500; ++j) {
        registry[i].chars[j] = (rand() % 95) + 32;
      }
    }

    if (args.situation == 3) {
      shuffle(registry, args.quantity);
    }

  } else if (args.situation == 2) {
    for (int i = args.quantity - 1; i >= 0; --i) {
      registry[i].key = i;
      registry[i].data = rand();

      for (int j = 0; j < 500; ++j) {
        registry[i].chars[j] = (rand() % 95) + 32;
      }
    }
  }

  FILE *output = createFile();
  for (int k = 0; k < args.quantity; ++k) {
    fwrite(&registry[k], sizeof(Registry), 1, output);
  }

  free(registry);
  fclose(output);
  return;
}
