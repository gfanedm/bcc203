#include "file.h"

FILE *openFile() {
  FILE *input;
  if ((input = fopen("registros.bin", "r+b")) == NULL) {
    printf("Erro na abertura do arquivo de registros.\n");
    return NULL;
  } else {
    return input;
  }
}

FILE *createFile() {
  FILE *input;
  if ((input = fopen("registros.bin", "w+b")) == NULL) {
    printf("Erro na abertura do arquivo de registros.\n");
    return NULL;
  } else {
    return input;
  }
}
