

#include "sequentialAccess.h"

Index* createIndex(Arguments args) {
  FILE* input = openFile();
  Registry temp;

  int indexSize = (args.quantity + PAGE_SIZE - 1) / PAGE_SIZE;
  Index* index = new Index[indexSize];

  for (int i = 0; i < indexSize; i++) {
    index[i].position = i;
    fread(&temp, sizeof(Registry), 1, input);
    index[i].key = temp.key;
    fseek(input, sizeof(Registry) * (PAGE_SIZE - 1), 1);
  }

  fclose(input);
  return index;
}

bool search(long int pos, Registry* registry, long int* comp,
            long int* transfer) {
  FILE* arq = openFile();

  Registry* page = new Registry[PAGE_SIZE];

  int qnt_reg = PAGE_SIZE;
  if (pos == -1) {
    fseek(arq, 0, SEEK_END);
    qnt_reg = (ftell(arq) / sizeof(Registry)) % PAGE_SIZE;
    *transfer += 2;
  }

  fseek(arq, pos * 4 * sizeof(Registry), 0);
  fread(page, sizeof(Registry), qnt_reg, arq);

  *transfer += 2;

  fclose(arq);

  for (int i = 0; i < qnt_reg; i++) {
    (*comp)++;
    if (page[i].key == registry->key) {
      *registry = page[i];
      return true;
    }
  }
  return false;
}

long int searchSequentialIndex(Arguments args, long int* comp) {
  int i = 0;
  long int pos;

  Index* index = createIndex(args);

  int indexSize = (args.quantity + PAGE_SIZE - 1) / PAGE_SIZE;
  (*comp)++;

  while (i < indexSize && index[i].key <= args.key) {
    pos = index[i].position;
    (*comp)++;
    i++;
  }

  if (pos == indexSize) pos = -1;
  return pos;
}

long int searchBinaryIndex(Index* index, int l, int* mid, int r, int x) {
  if (r >= l) {
    *mid = l + (r - l) / 2;

    if (index[*mid].key > x)
      return searchBinaryIndex(index, l, mid, *mid - 1, x);
    return searchBinaryIndex(index, *mid + 1, mid, r, x);
  }

  return index[*mid - 1].position;
}
