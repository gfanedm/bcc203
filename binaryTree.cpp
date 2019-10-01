#include "binaryTree.h"

bool insertBinaryTree(BinTree tree, Registry data, int cont, int sit,
                      long* transf, long* comp) {
  FILE* file = openFile();
  cout << "CUCUUCUCU" << endl;

  // tree a ser inserido na arvore!
  tree.notch = data;
  tree.left = -1;
  tree.right = -1;

  fseek(file, 0, SEEK_END);
  fwrite(&tree, sizeof(BinTree), 1, file);

  long aux;

  if (sit == 1 || sit == 2) {
    // Trapaca na criacao da arvore! Dados crescentes ou decrescentes!
    // Volta ao penultimo no da arvore!

    aux = sizeof(BinTree);

    fseek(file, -2 * aux, SEEK_CUR);
    fread(&tree, sizeof(BinTree), 1, file);

    (*transf)++;

    // Voltar novamente ao penultimo no!
    fseek(file, -aux, SEEK_CUR);
  } else {
    // Voltar ao inicio da arvore, lê o nó da raiz e voltar para o inicio!

    rewind(file);
    fread(&tree, sizeof(BinTree), 1, file);
    (*transf)++;
    rewind(file);
  }

  cout << "=================" << endl;
  while (1) {
    // Verifica a posicao do novo registro!

    (*comp)++;
    if (data.key < tree.notch.key) {
      if (tree.left == -1) {
        // Salva o nó modificado
        tree.left = cont;
        fwrite(&tree, sizeof(BinTree), 1, file);

        cout << "aquipassouuu" << endl;
        break;
      } else {
        aux = sizeof(BinTree);

        fseek(file, tree.left * sizeof(BinTree), SEEK_SET);
        fread(&tree, sizeof(BinTree), 1, file);

        // cout << "tree = " << tree.left << " / " << tree.right << " / "
        //      << tree.notch.key << endl;
        (*transf)++;

        fseek(file, -aux, SEEK_CUR);
        // cout << "retornandos" << endl;
        // Retorna ao inicio do nó encontrado no fseek anterior
      }
    } else {
      if (tree.right == -1) {
        tree.right = cont;
        fwrite(&tree, sizeof(BinTree), 1, file);
        cout << "adsdsaadsadsdasadsdasadsdsa" << endl;
        break;
      } else {
        aux = sizeof(BinTree);

        fseek(file, tree.right * sizeof(BinTree), SEEK_SET);
        fread(&tree, sizeof(BinTree), 1, file);

        (*transf)++;

        fseek(file, -aux, SEEK_CUR);
        cout << "treee" << endl;
      }
    }
  }
  return true;
}

bool searchBinaryTree(BinTree tree, Registry* data, long* transf, long* comp) {
  FILE* file = openFile();
  while (fread(&tree, sizeof(BinTree), 1, file) == 1) {
    (*transf)++;

    if (data->key == tree.notch.key) {
      (*comp)++;
      *data = tree.notch;

      return true;
    } else {
      if (data->key < tree.notch.key) {
        (*comp)++;

        if (tree.left != -1) {
          fseek(file, tree.left * sizeof(BinTree), SEEK_SET);
        } else {
          return false;
        }

      } else {
        (*comp)++;

        if (tree.right != -1) {
          fseek(file, tree.right * sizeof(BinTree), SEEK_SET);
        } else {
          return false;
        }
      }
    }
  }
  return true;
}
