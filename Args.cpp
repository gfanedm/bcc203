#include "args.h"

int validateArguments(int argc, char *argv[], Arguments *args) {
  if (argc < 4 || argc > 6) {
    cout << "Argumentos incorretos. O modelo correto é:\n";
    cout << "<método> <quantidade> <situação> <chave> [-P]\n";
    return 0;
  }

  args->method = atoi(argv[1]);
  args->quantity = atoi(argv[2]);
  args->situation = atoi(argv[3]);
  args->key = atoi(argv[4]);

  if (args->method < 1 || args->method > 4) {
    printf("Argumento <método> incorreto. Deve ser entre 1 e 4.\n");
    return 0;
  }

  if (args->situation < 1 || args->situation > 3) {
    printf("Argumento <situação> incorreto. Deve ser entre 1, 2 e 3.\n");
    return 0;
  }

  if (*argv[5] == 'P') {
    args->show = true;
  } else {
    args->show = false;
  }

  return 1;
}
