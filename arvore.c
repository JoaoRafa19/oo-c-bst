#include "arvore.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

 #define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

No* _insere(No* a, int info){
    if (a == NULL){
        No * arv = (No* ) malloc(sizeof(No));
        arv->esq = NULL;
        arv->dir = NULL;
        arv->info = info;
        return arv;
    }else{
        if(info < a->info)
        {
            a->esq = _insere(a -> esq, info);
        }else {
            a ->dir =  _insere(a->dir, info);
        }
        return a;

    }
}

void insere(Arvore * arv, int info){
    (* arv)._raiz = _insere(arv->_raiz, info);
}


 void printNormal(No* root){
    if(root == NULL) return;
    printNormal(root->esq);
    printf("%d-", root->info);
    printNormal(root->dir);

 }

 int getcol(int h) {
    if (h == 1)
        return 1;
    return getcol(h - 1) + getcol(h - 1) + 1;
}

 int height(No *root) {
    if (root == NULL)
        return 0;
    return max(height(root->esq), height(root->dir)) + 1;
}

void internalPrint(int **M, No *root, int col, int row, int height) {
    if (root == NULL)
        return;
    M[row][col] = root->info;
    internalPrint(M, root->esq, col - pow(2, height - 2), row + 1, height - 1);
    internalPrint(M, root->dir, col + pow(2, height - 2), row + 1, height - 1);
}

void TreePrinter(No* tree) {
     int h = height(tree);
    int col = getcol(h);
    int **M = (int **) calloc(h, sizeof(int *));
    for (int i = 0; i < h; i++) {
        M[i] = (int *) calloc(col, sizeof(int));//new int[col];
    }
    internalPrint(M, tree, col / 2, 0, h);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < col; j++) {
            if (M[i][j] == 0)
                printf("  ");
            else
                printf("%d ", M[i][j]);//cout << M[i][j] << " ";
        }
        printf("\n");//cout << endl;
    }
}

void printPostOrder(No * root, int level)
{
     if (root == NULL)
        return;
 
    // Increase distance between levels
    level += 10;
 
    // Process right child first
    printPostOrder(root->dir, level);
 
    // Print current node after space
    // count
    printf("\n");
    for(int i =0 ; i < level; i ++) printf(" ");
    printf("%d\n", root->info);
 
    // Process left child
    printPostOrder(root->esq, level);
}

void printTree(Arvore* arv){
    // printf("Arvore \n");
    // printNormal(arv->_raiz);
    // return;
    // printPostOrder(arv->_raiz, 0);
    TreePrinter(arv->_raiz);
}

bool _buscaInterno(No* root, int info, No** result){
    if(root == NULL) return false;

    if (info == root->info){
        *result = root;
        return true;
    }
    else {
        return _buscaInterno( info < root->info ? root->esq : root->dir, info, result);
    }
}

bool busca(Arvore *arv, int info, No** resultado){
    if( arv == NULL){
        resultado = NULL;
        return false;
    }
    else {
        if (arv->_raiz != NULL){
            *resultado = (No* ) malloc(sizeof(No));
            return _buscaInterno(arv->_raiz, info, resultado);
        } else {
            return false;
        }
    }
}

bool ehFolha(No* node){
    return node->esq == NULL && node->dir == NULL;
}

void antecessor(No* q, No** r){
   No* aux;
   if( (*r)->dir != NULL){
    antecessor(q, &(*r)->dir);
    return;
   }
   q->info = (*r)->info;
   aux = *r;
   *r = (*r)->esq;
   free(aux);

}

No* _remove(No* root, int info){
    if (root == NULL ){
        return NULL;
    }

    else {
        if (info < root -> info){
            root->esq = _remove(root->esq, info);
        }else if(info > root->info){
            root->dir = _remove(root->dir, info);
        }

        //substituicao

        if( root -> dir == NULL && root->esq != NULL){
            root = root->esq;
        }if( root -> dir != NULL && root->esq != NULL){
            antecessor(root, &root->esq );
        }
        if(root->esq == NULL && root ->dir != NULL){
            root = root->dir;
        }
    }

    return root;
}
void removeNode(Arvore*arv, int info){
    arv->_raiz = _remove(arv->_raiz, info);
}


//* Deve ser a ultima função declarada
// no arquivo .c
Arvore* cria(){
    struct arvore * arv = (Arvore *) malloc(sizeof(Arvore));
    arv->_raiz = NULL;
    arv->insere = &insere;
    arv->busca = &busca;
    arv->remove = &removeNode;
    arv->imprime = &printTree;

}