#include "arvore.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief Função de verificação de maior valor
 * @param a valor a ser verificado
 * @param b valor a ser verificado
 */
#define max(a, b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

/**
 * @brief Método de inserção recursiva na arvore
 * @param a nó raiz/atual a ser verificado
 * @param info valor a ser adicionado na arvore
 */
No *_insere(No *a, int info)
{
    if (a == NULL)
    {
        No *arv = (No *)malloc(sizeof(No));
        arv->esq = NULL;
        arv->dir = NULL;
        arv->info = info;
        return arv;
    }
    else
    {
        if (info < a->info)
        {
            a->esq = _insere(a->esq, info);
        }
        else
        {
            a->dir = _insere(a->dir, info);
        }
        return a;
    }
}

/**
 * @brief Encapsulamento do método de inserção da arvore
 * @param arv arvore a ser inserida
 * @param info valor a ser adicionado na arvore
 */
void insere(Arvore *arv, int info)
{
    (*arv)._raiz = _insere(arv->_raiz, info);
}

/**
 * @brief Método de calculo do número de colunas na matriz
 * para impressão da arvore
 * @param h altura da arvore
 */
int getcol(int h)
{
    if (h == 1)
        return 1;
    return getcol(h - 1) + getcol(h - 1) + 1;
}

/**
 * @brief Retorna a profundidade do nó mais abaixo em relação ao nó passado como parâmetro
 * @param root nó raiz
 */
int height(No *root)
{
    if (root == NULL)
        return 0;
    return max(height(root->esq), height(root->dir)) + 1;
}

/**
 * @brief Percurso recursivo de preenchimento da matriz pelos elementos da arvore
 * @param M endereço da matriz a ser preenchida
 * @param root nó atual/raiz da arvore
 * @param col indice da coluna a ser preenchida
 * @param row indice da linha a ser preenchida
 * @param height altura do nó atual
 */
void internalPrint(int **M, No *root, int col, int row, int height)
{
    if (root == NULL)
        return;
    M[row][col] = root->info;
    internalPrint(M, root->esq, col - pow(2, height - 2), row + 1, height - 1);
    internalPrint(M, root->dir, col + pow(2, height - 2), row + 1, height - 1);
}

/**
 * @brief Impressão por método de matriz da arvore
 * @param tree Nó raiz da arvore a ser impressa
 */
void TreePrinter(No *tree)
{
    int h = height(tree);
    int col = getcol(h);
    // aloca o vetor de ponteiros para vetores
    int **M = (int **)calloc(h, sizeof(int *));

    // preenche o vetor(matriz) com vetores dinamicamente alocados
    for (int i = 0; i < h; i++)
    {
        M[i] = (int *)calloc(col, sizeof(int)); // new int[col];
    }
    // preenche a matrix com os valores da arvore
    internalPrint(M, tree, col / 2, 0, h);

    // percore a matriz imprimindo os valores
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (M[i][j] == 0)
                printf("  ");
            else
                printf("%d ", M[i][j]); // cout << M[i][j] << " ";
        }
        printf("\n"); // cout << endl;
    }
    free(M);
}

/**
 * @brief encapsulamento do método de impressão por matriz da arvore
 * @param arv Arvore a ser buscada
 */
void printTree(Arvore *arv)
{
    TreePrinter(arv->_raiz);
}

/**
 * @brief Faz uma busca binária pelos nós da arvore e retorna o resultado da busca
 * @param root Nó raiz por onde se inicia a busca
 * @param info Conteúdo a ser buscado
 * @param resultado endereço de referência para cópia de resultado de busca
 */
bool _buscaInterno(No *root, int info, No **result)
{
    if (root == NULL)
        return false;

    if (info == root->info)
    {
        *result = root;
        return true;
    }
    else
    {
        return _buscaInterno(info < root->info ? root->esq : root->dir, info, result);
    }
}

/**
 * @brief Realiza uma busca na arvore e retorna se o elemento existe ou não (true/false)
 * e pode retornaro Nó resultado pela varíavel
 * @param arv Referencia da arvore onde será realizada a busca
 * @param info Conteúdo a ser buscado
 * @param resultado endereço de referência para cópia de resultado de busca
 */
bool busca(Arvore *arv, int info, No **resultado)
{
    if (arv == NULL)
    {
        resultado = NULL;
        return false;
    }
    else
    {
        if (arv->_raiz != NULL)
        {
            *resultado = (No *)malloc(sizeof(No));
            return _buscaInterno(arv->_raiz, info, resultado);
        }
        else
        {
            return false;
        }
    }
}

/**
 * @brief Verifica se um nó é uma folha ( tem ambos os filhos Nulos)
 * @param node Nó a ser verificado
 */
bool ehFolha(No *node)
{
    return node->esq == NULL && node->dir == NULL;
}

/**
 * @brief Busca o maior elemento da sub-arvore da esquerda de um nó
 * @param root nó pai a ser substituído pelo antecessor
 * @param esq nó filho a esquerda de `root` a ser removido e copiado
 */
void antecessor(No *root, No **esq)
{
    No *aux;
    if ((*esq)->dir != NULL)
    {
        antecessor(root, &(*esq)->dir);
        return;
    }
    root->info = (*esq)->info;
    aux = *esq;
    *esq = (*esq)->esq;
    free(aux);
}

/**
 * @brief Método para remoção recursiva de um nó com a informação desejada
 * @param root Referencia do nó raiz ou nó interno a ser removido
 * @param info Informação contida no nó que deseja remover
 */
No *_remove(No *root, int info)
{
    if (root == NULL)
    {
        return NULL;
    }

    else
    {
        if (info < root->info)
        {
            root->esq = _remove(root->esq, info);
        }
        else if (info > root->info)
        {
            root->dir = _remove(root->dir, info);
        }

        // substituicao

        if (info == root->info)
        {
            if (ehFolha(root))
            {
                free(root);
                return NULL;
            }
            if (root->dir == NULL && root->esq != NULL)
            {
                root = root->esq;
            }
            if (root->dir != NULL && root->esq != NULL)
            {
                antecessor(root, &root->esq);
            }
            if (root->esq == NULL && root->dir != NULL)
            {
                root = root->dir;
            }
        }
    }

    return root;
}

/**
 * @brief Encapsulamento da remoção de nó da arvore
 * @param arv referencia da arvore que terá a raiz alterada
 * @param info cópia do id do nó que deve ser removido
 */
void removeNode(Arvore *arv, int info)
{
    arv->_raiz = _remove(arv->_raiz, info);
}

//* Deve ser a ultima função declarada
// no arquivo .c
Arvore *cria()
{
    struct arvore *arv = (Arvore *)malloc(sizeof(Arvore));
    arv->_raiz = NULL;
    arv->insere = &insere;
    arv->busca = &busca;
    arv->remove = &removeNode;
    arv->imprime = &printTree;
}