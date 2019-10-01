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

FILE *openBooks() {
  FILE *input;
  if ((input = fopen("livros.txt", "r")) == NULL) {
    printf("Erro na abertura do arquivo de livros.\n");
    return NULL;
  } else {
    return input;
  }
}

FILE *openBin() {
  FILE *input;
  if ((input = fopen("arvore.bin", "w+b")) == NULL) {
    printf("Erro na abertura do arquivo de livros.\n");
    return NULL;
  } else {
    return input;
  }
}