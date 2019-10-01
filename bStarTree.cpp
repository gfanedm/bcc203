#include "bStarTree.h"

void initializeBStarTree(PointerPlus* tree) { *tree = NULL; }

void bTreeStar(FILE** file, int qtd, PointerPlus* tree, int& nTransfer,
               int& nCompare) {
  initializeBStarTree(tree);
  Registry registry;
  nCompare++;

  while ((fread(&registry, sizeof(Registry), 1, *file) == 1) && qtd > 0) {
    nTransfer++;
    nCompare++;

    insertBStarTree(&registry, tree, nTransfer, nCompare);
    qtd--;
  }

  fflush(stdout);
}

void insertBStarTree(Registry* registry, PointerPlus* pointer, int& nTransfer,
                     int& nCompare) {
  short grown;
  Registry registryReturn;
  Page *pageReturn, *pageTemp;
  Registry temp = *registry;
  nCompare++;

  // Se a árvore estiver vazia
  if (*pointer == NULL) {
    pageTemp = (Page*)malloc(sizeof(Page));
    pageTemp->type = Extern;

    // n vai ter o seu primeiro item
    pageTemp->Union.UnionExtern.n = 1;

    // recebe o item
    pageTemp->Union.UnionExtern.items[0] = temp;
    *pointer = pageTemp;

    // apontador para próxima página recebe NULL
    pageTemp->Union.UnionExtern.next = NULL;
    return;

  } else {
    // cresce uma pagina interna
    insBStarTree(temp, *pointer, &grown, &registryReturn, &pageReturn,
                 nTransfer, nCompare);

    nCompare++;

    // verifica se já chegou na raiz
    if (grown) {
      Page* page = (Page*)malloc(sizeof(Page));
      page->type = Intern;

      // n vai ter o seu primeiro item
      page->Union.UnionIntern.n = 1;
      // insere o item na primeira posicao do vetor
      page->Union.UnionIntern.key[0] = registryReturn.key;

      // ponteiro para NULL
      page->Union.UnionIntern.pointer[1] = pageReturn;
      page->Union.UnionIntern.pointer[0] = *pointer;

      *pointer = page;
    }
  }
}

void insBStarTree(Registry registry, PointerPlus pointer, short* grown,
                  Registry* registryReturn, PointerPlus* pointerReturn,
                  int& nTransfer, int& nCompare) {
  long i = 1;

  nCompare++;
  if (pointer->type == Extern) {
    nCompare++;
    // pagina com espaco
    if (pointer->Union.UnionExtern.n < MM2) {
      // cout << "Externa: " << pointer->Union.UnionExtern.items[i - 1].key;

      *registryReturn = registry;

      insertPageBStarTree(pointer, *registryReturn, *pointerReturn, nTransfer,
                          nCompare);

      *grown = false;
      return;
    } else {
      // Overflow: Pagina tem que ser dividida
      // Depois de achar a página externa que deve colocar o item

      *registryReturn = registry;
      *pointerReturn = NULL;
      nCompare++;
      // procurando a posição
      while (i < pointer->Union.UnionExtern.n &&
             registry.key > pointer->Union.UnionExtern.items[i - 1].key) {
        i++;
        nCompare++;
      }
      // pagina sem espaço, divide
      PointerPlus pointerTemp;
      nCompare++;

      if (registry.key < pointer->Union.UnionExtern.items[i - 1].key) i--;

      pointerTemp = (PointerPlus)malloc(sizeof(Page));

      pointerTemp->type = Extern;
      pointerTemp->Union.UnionExtern.next = pointer->Union.UnionExtern.next;

      pointer->Union.UnionExtern.next = pointerTemp;
      pointerTemp->Union.UnionExtern.n = 0;
      nCompare++;

      // empresta elemento para a pagina à direita
      if (i < MMp + 1) {
        insertPageBStarTree(pointerTemp,
                            pointer->Union.UnionExtern.items[MM2 - 1],
                            *pointerReturn, nTransfer, nCompare);
        pointer->Union.UnionExtern.n--;
        insertPageBStarTree(pointer, *registryReturn, *pointerReturn, nTransfer,
                            nCompare);
      } else {
        // insere direto na página
        insertPageBStarTree(pointerTemp, *registryReturn, *pointerReturn,
                            nTransfer, nCompare);
      }
      // transfere metade direita para a nova página
      for (long j = 1; j <= MMp; j++) {
        nCompare++;
        insertPageBStarTree(pointerTemp,
                            pointer->Union.UnionExtern.items[MM2 - j],
                            *pointerReturn, nTransfer, nCompare);
      }
      pointer->Union.UnionExtern.n = MMp;
      *registryReturn = pointer->Union.UnionExtern.items[MMp];
      *pointerReturn = pointerTemp;
      *grown = true;

      return;
    }
  }

  // Overflow: Pagina tem que ser dividida

  nCompare++;

  // procurando a posição
  while (i < pointer->Union.UnionIntern.n &&
         registry.key > pointer->Union.UnionIntern.key[i - 1]) {
    i++;
    nCompare++;
  }

  nCompare++;

  if (registry.key < pointer->Union.UnionIntern.key[i - 1]) i--;

  insBStarTree(registry, pointer->Union.UnionIntern.pointer[i], grown,
               registryReturn, pointerReturn, nTransfer, nCompare);
  nCompare++;

  if (!*grown) return;
  nCompare++;

  if (pointer->Union.UnionIntern.n < MM2) {
    insertPageBStarTree(pointer, *registryReturn, *pointerReturn, nTransfer,
                        nCompare);
    *grown = false;  // chave existente na arvore
    return;
  }

  nCompare++;
  if (registry.key == pointer->Union.UnionIntern.key[i - 1]) {
    *grown = false;  // chave existente na arvore
    return;
  }
  PointerPlus pointerTemp;
  pointerTemp = (PointerPlus)malloc(sizeof(Page));
  pointerTemp->type = Intern;
  pointerTemp->Union.UnionIntern.n = 0;
  pointerTemp->Union.UnionIntern.pointer[0] = NULL;

  Registry registryTemp;
  nCompare++;

  // empresta elemento para a pagina à direita
  if (i < MMp + 1) {
    registryTemp.key = pointer->Union.UnionIntern.key[MM2 - 1];
    insertPageBStarTree(pointerTemp, registryTemp,
                        pointer->Union.UnionIntern.pointer[MM2], nTransfer,
                        nCompare);

    pointer->Union.UnionIntern.n--;

    insertPageBStarTree(pointer, *registryReturn, *pointerReturn, nTransfer,
                        nCompare);
  } else {
    // insere direto na página
    insertPageBStarTree(pointerTemp, *registryReturn, *pointerReturn, nTransfer,
                        nCompare);
  }
  // transfere metade direita para a nova página
  for (long j = MMp + 2; j <= MM2; j++) {
    nCompare++;
    registryTemp.key = pointer->Union.UnionIntern.key[j - 1];
    insertPageBStarTree(pointerTemp, registryTemp,
                        pointer->Union.UnionIntern.pointer[j], nTransfer,
                        nCompare);
  }
  pointer->Union.UnionIntern.n = MMp;
  pointerTemp->Union.UnionIntern.pointer[0] =
      pointer->Union.UnionIntern.pointer[MMp + 1];

  registryReturn->key = pointer->Union.UnionIntern.key[MMp];
  *pointerReturn = pointerTemp;
  return;
}

void insertPageBStarTree(PointerPlus pointer, Registry registry,
                         PointerPlus pointerRight, int& nTransfer,
                         int& nCompare) {
  short find;
  int k;
  nCompare++;
  if (pointer->type == Extern) {
    // cout << "TIPO EXTERNA: " << registry.key << endl;
    k = pointer->Union.UnionIntern.n;

    // se existe posicao para inserir
    find = (k > 0);

    // comparacao de caso nao entre no while
    nCompare++;

    while (find) {
      nCompare++;

      if (registry.key >= pointer->Union.UnionExtern.items[k - 1].key) {
        find = false;
        break;
      }
      // Mudando de posição
      pointer->Union.UnionExtern.items[k] =
          pointer->Union.UnionExtern.items[k - 1];
      k--;

      // comparacao do k < 1
      nCompare++;
      if (k < 1) find = false;
    }

    pointer->Union.UnionExtern.items[k] = registry;
    pointer->Union.UnionExtern.n++;

  } else {
    // cout << "TIPO INTERNA: " << registry.key << endl;

    k = pointer->Union.UnionIntern.n;

    // se existe posicao para inserir
    find = (k > 0);

    // comparacao de caso nao entre no while
    nCompare++;

    while (find) {
      nCompare++;
      if (registry.key >= pointer->Union.UnionIntern.key[k - 1]) {
        find = false;
        break;
      }

      // Mudando de posição
      pointer->Union.UnionIntern.key[k] = pointer->Union.UnionIntern.key[k - 1];
      pointer->Union.UnionIntern.pointer[k + 1] =
          pointer->Union.UnionIntern.pointer[k];
      k--;

      nCompare++;

      // comparacao do k < 1
      if (k < 1) find = false;
    }

    // Achou Posição
    pointer->Union.UnionIntern.key[k] = registry.key;
    pointer->Union.UnionIntern.pointer[k + 1] = pointerRight;
    pointer->Union.UnionIntern.n++;
    return;
  }
}

bool searchBStarTree(Registry* registry, PointerPlus* pointer, int& nTransfer,
                     int& nCompare) {
  long i;

  int key = registry->key;

  nCompare++;

  if ((*pointer)->type == Intern) {
    i = 1;
    nCompare++;

    // pesquisa sequencial nas páginas internas
    while (i < (*pointer)->Union.UnionIntern.n &&
           key > (*pointer)->Union.UnionIntern.key[i - 1]) {
      nCompare++;
      i++;
    }

    nCompare++;

    // ativação recursiva, só para quando achar a página folha
    if (key < (*pointer)->Union.UnionIntern.key[i - 1])
      return searchBStarTree(registry,
                             &(*pointer)->Union.UnionIntern.pointer[i - 1],
                             nTransfer, nCompare);
    else
      return searchBStarTree(registry,
                             &(*pointer)->Union.UnionIntern.pointer[i],
                             nTransfer, nCompare);
  }
  i = 1;

  nCompare++;

  // pesquisando na página folha
  while (i < (*pointer)->Union.UnionExtern.n &&
         key > (*pointer)->Union.UnionExtern.items[i - 1].key) {
    nCompare++;
    i++;
  }

  nCompare++;
  if (key == (*pointer)->Union.UnionExtern.items[i - 1].key) {
    *registry = (*pointer)->Union.UnionExtern.items[i - 1];
    return true;
  } else
    return false;
}

void printBTreeStar(PointerPlus pointer) {
  int i = 0;

  PointerPlus aux;
  if (pointer == NULL) return;

  if (pointer->type == Intern) {
    while (i <= pointer->Union.UnionIntern.n) {
      printBTreeStar(pointer->Union.UnionIntern.pointer[i]);
      if (i != pointer->Union.UnionIntern.n)
        printf("Interno : %d\n", pointer->Union.UnionIntern.key[i]);
      i++;
    }
  } else {
    cout << "Externo: ";
    aux = pointer;
    for (int j = 0; j < pointer->Union.UnionExtern.n; j++) {
      cout << "(" << j << ")"
           << " | " << aux->Union.UnionExtern.items[j].key << endl;
    }
    cout << endl;
  }
}

void star(int key) {
  FILE* file = openFile();
  Registry aux;
  PointerPlus pointer;

  int cont = 0, trans = 0;
  clock_t time = 0;
  clock_t proccess = 0;

  initializeBStarTree(&pointer);

  proccess = clock();
  // preenche a arvore
  bTreeStar(&file, TAM, &pointer, trans, cont);

  proccess = clock() - proccess;
  proccess = ((float)proccess) * 1000.0 / CLOCKS_PER_SEC;
  cout << "Tempo de pre-processamento: " << proccess << "MS" << endl;
  cout << "Quantidade de transferencias: " << trans << endl;
  cout << "Comparacoes no pre-processamento : " << cont << endl;

  // zera o contador para poder contar as comparacoes na pesquisa
  cont = 0;
  aux.key = key;

  time = clock();
  if (searchBStarTree(&aux, &pointer, trans, cont) == true) {  // se achar

    cout << "\nO Livro : " << aux.chars << endl;
    cout << "Codigo    : " << aux.data << endl;
    cout << "Chave     : " << aux.key << endl;
    cout << "Comparacoes feitas : " << cont << endl;

    // calcula o tempo de execucao
    time = clock() - time;
    time = ((float)time) * 1000.0 / CLOCKS_PER_SEC;
    cout << "Tempo de pesquisa: " << time << "ms " << endl;

  } else {
    cout << "\nO livro de chave : " << aux.key
         << " nao foi encontrado no catalogo." << endl;
  }
}