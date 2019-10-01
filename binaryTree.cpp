#include "binaryTree.h"

bool insertBinaryTree(BinTree registry, BinData data, int cont, int sit,
                      long* transf, long* comp) {
  FILE* tree = openFile();

  // registry a ser inserido na arvore!
  registry.notch = data;
  registry.left = -1;
  registry.right = -1;

  fseek(tree, 0, SEEK_END);
  fwrite(&registry, sizeof(BinTree), 1, tree);

  long aux;

  if (sit == 1 || sit == 2) {
    // Trapaca na criacao da arvore! Dados crescentes ou decrescentes!
    // Volta ao penultimo no da arvore!

    aux = sizeof(BinTree);

    fseek(tree, -2 * aux, SEEK_CUR);
    fread(&registry, sizeof(BinTree), 1, tree);

    (*transf)++;

    // Voltar novamente ao penultimo no!
    fseek(tree, -aux, SEEK_CUR);
  } else {
    // Voltar ao inicio da arvore, lê o nó da raiz e voltar para o inicio!

    rewind(tree);
    fread(&registry, sizeof(BinTree), 1, tree);
    (*transf)++;
    rewind(tree);
  }

  while (true) {
    // Verifica a posicao do novo regitro!

    (*comp)++;
    if (data.key < registry.notch.key) {
      if (registry.left == -1) {
        // Salva o nó modificado
        registry.left = cont;
        fwrite(&registry, sizeof(BinTree), 1, tree);

        break;
      } else {
        aux = sizeof(BinTree);

        fseek(tree, registry.left * sizeof(BinTree), SEEK_SET);
        fread(&registry, sizeof(BinTree), 1, tree);

        (*transf)++;

        fseek(tree, -aux, SEEK_CUR);
        // Retorna ao inicio do nó encontrado no fseek anterior
      }
    } else {
      if (registry.right == -1) {
        registry.right = cont;
        fwrite(&registry, sizeof(BinTree), 1, tree);

        break;
      } else {
        aux = sizeof(BinTree);

        fseek(tree, registry.right * sizeof(BinTree), SEEK_SET);
        fread(&registry, sizeof(BinTree), 1, tree);

        (*transf)++;

        fseek(tree, -aux, SEEK_CUR);
      }
    }
  }
  return true;
}

bool searchBinaryTree(BinTree registry, BinData* data, long* transf,
                      long* comp) {
  FILE* tree = openFile();
  while (fread(&registry, sizeof(BinTree), 1, tree) == 1) {
    (*transf)++;

    if (data->key == registry.notch.key) {
      (*comp)++;
      *data = registry.notch;

      return true;
    } else {
      if (data->key < registry.notch.key) {
        (*comp)++;

        if (registry.left != -1) {
          fseek(tree, registry.left * sizeof(BinTree), SEEK_SET);
        } else {
          return false;
        }

      } else {
        (*comp)++;

        if (registry.right != -1) {
          fseek(tree, registry.right * sizeof(BinTree), SEEK_SET);
        } else {
          return false;
        }
      }
    }
  }
  return true;
}