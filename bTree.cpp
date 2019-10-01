#include "bTree.h"

struct Page {
  short n;
  Registry registry[MM];
  Pointer page[MM + 1];
};

void initialize(Pointer& tree) { tree = NULL; }

bool searchBTree(Registry* registry, Pointer pointer, int& comp) {
  long i = 1;

  comp++;
  if (pointer == NULL) {
    return false;
  }

  comp++;
  while (i < pointer->n && registry->key > pointer->registry[i - 1].key) {
    i++;
  }

  comp++;
  if (registry->key == pointer->registry[i - 1].key) {
    *registry = pointer->registry[i - 1];
    return true;
  }
  comp++;
  if (registry->key < pointer->registry[i - 1].key) {
    comp++;
    return searchBTree(registry, pointer->page[i - 1], comp);
  } else {
    return searchBTree(registry, pointer->page[i], comp);
  }
}

void insertOnPage(Pointer pointer, Registry registry, Pointer pointerDir,
                  int& comp) {
  short notFind;
  int k = pointer->n;
  notFind = (k > 0);

  while (notFind) {
    comp++;
    if (registry.key >= pointer->registry[k - 1].key) {
      notFind = false;
      break;
    }

    pointer->registry[k] = pointer->registry[k - 1];
    pointer->page[k + 1] = pointer->page[k];
    k--;

    comp++;
    if (k < 1) {
      notFind = false;
    }
  }
  pointer->registry[k] = registry;
  pointer->page[k + 1] = pointerDir;
  pointer->n++;
}

void insertRegistry(Registry registry, Pointer pointer, short* grown,
                    Registry* registryReturn, Pointer* pointerReturn,
                    int& comp) {
  long i = 1;
  long j;
  Pointer tempPointer;

  comp++;
  if (pointer == NULL) {
    *grown = true;
    *registryReturn = registry;
    *pointerReturn = NULL;
    return;
  }

  while (i < pointer->n && registry.key > pointer->registry[i - 1].key) {
    i++;
    comp++;
  }

  comp++;
  if (registry.key == pointer->registry[i - 1].key) {
    cout << "Erro : Registro ja esta presente \n";
    *grown = false;
    return;
  }

  comp++;
  if (registry.key < pointer->registry[i - 1].key) i--;

  insertRegistry(registry, pointer->page[i], grown, registryReturn,
                 pointerReturn, comp);

  comp++;
  if (!*grown) {
    return;
  }

  comp++;
  if (pointer->n < MM) {
    insertOnPage(pointer, *registryReturn, *pointerReturn, comp);
    *grown = false;
    return;
  }

  tempPointer = (Pointer)malloc(sizeof(Page));
  tempPointer->n = 0;
  tempPointer->page[0] = NULL;

  if (i < M + 1) {
    insertOnPage(tempPointer, pointer->registry[MM - 1], pointer->page[MM],
                 comp);
    pointer->n--;
    insertOnPage(pointer, *registryReturn, *pointerReturn, comp);
  } else {
    insertOnPage(tempPointer, *registryReturn, *pointerReturn, comp);
  }

  for (j = M + 2; j <= MM; j++) {
    insertOnPage(tempPointer, pointer->registry[j - 1], pointer->page[j], comp);
    pointer->n = M;
    tempPointer->page[0] = pointer->page[M + 1];
    *registryReturn = pointer->registry[M];
    *pointerReturn = tempPointer;
  }
}

void insert(Registry registry, Pointer* pointer, int& comp) {
  short grown;
  Registry registryReturn;
  Page *pageReturn, *pointerTemp;

  insertRegistry(registry, *pointer, &grown, &registryReturn, &pageReturn,
                 comp);

  if (grown) {
    pointerTemp = (Page*)malloc(sizeof(Page));
    pointerTemp->n = 1;
    pointerTemp->registry[0] = registryReturn;
    pointerTemp->page[1] = pageReturn;
    pointerTemp->page[0] = *pointer;
    *pointer = pointerTemp;
  }
}

void bTree(int key) {
  Registry aux;
  Pointer pointer;
  Registry registry;

  int cont = 0, comp = 0;
  int transferences = 0;
  clock_t timeSearch = 0;
  clock_t processment = 0;

  initialize(pointer);

  FILE* file = openFile();

  processment = clock();
  while (fread(&registry, sizeof(registry), 1, file) == 1) {
    insert(registry, &pointer, comp);
    transferences++;
  }

  processment = clock() - processment;
  processment = ((float)processment) * 1000.0 / CLOCKS_PER_SEC;
  cout << "Tempo de pre-processamento: " << processment << "ms" << endl;
  cout << "Quantidade de transferencias: " << transferences << endl;
  cout << "Comparacoes no pre-processamento : " << comp << endl;

  aux.key = key;

  timeSearch = clock();
  if (searchBTree(&aux, pointer, cont) == true) {
    cout << "\nO Livro : " << aux.chars << endl;
    cout << "Codigo    : " << aux.data << endl;
    cout << "Chave     : " << aux.key << endl;
    cout << "Comparacoes feitas : " << cont << endl;

    timeSearch = clock() - timeSearch;
    timeSearch = ((float)timeSearch) * 1000.0 / CLOCKS_PER_SEC;
    cout << "Tempo de pesquisa: " << setprecision(4) << timeSearch << "ms "
         << endl;

  } else {
    cout << "\nO livro de chave : " << aux.key
         << " nao foi encontrado no catalogo." << endl;
  }
}
