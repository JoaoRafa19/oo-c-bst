# Arvore BST com pseudo orientação a objetos


## Introdução

Este projeto foi desenvolvido para a disciplina de Estrutura de Dados II, do curso de Ciência da Computação da Universidade Federal de Viçosa - Campus Florestal.

O objetivo do projeto é implementar uma árvore binária de busca (BST) com pseudo orientação a objetos, utilizando a linguagem de programação C.

## Definição da estrutura

### Tipos Abstratos

#### Tipo booleano

``` c
#ifndef arvore_h
#define arvore_h

#define true 1
#define false 0

typedef int bool;
```

Definiçao do tipo `bool` para `int` para que seja possível utilizar o tipo `bool` na linguagem C
.

---

#### Tipo No

```c
typedef struct arvore Arvore;


typedef struct no  No;
struct no {
    int info;
    No* esq;
    No* dir;
};
```

Redefinição do tipo estrutura para o tipo Arvore e No, e criação da estrutura No que será utilizada para representar os nós da árvore.

---

#### Tipo Arvore

``` c
struct arvore {
    No *_raiz;
    void(*insere)(Arvore* , int );
    bool(*busca)(Arvore* , int , No* );
    void(*remove)(Arvore* , int );
    void(*imprime)(Arvore* );
};
```

```c
Arvore* cria();

#endif /* arvore_h */
```

Na estrutura `struct arvore` foi usado a estratégia de encapsulamento dos métodos relacionados a estrutura usando ponteiros para funções para que o usuário não tenha acesso direto aos métodos, sendo assim, o usuário só pode acessar os métodos através da estrutura `Arvore*`.

As funções relacioadas a estrutura são atribuidos no arquivo `arvore.c`, onde serão definidos e implementados.

## Métodos

### Criação da árvore

``` c
Arvore* cria();
```
Único método externo usado fora da estrutura, definido como contrutor da arvore, onde é alocado espaço na memória para a estrutura `Arvore*` e inicializado os atributos da estrutura.

``` c
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
```
os metodos atribuidos na estrutura **devem** ser declarados antes da função `cria()`.

---

### Métodos internos auxiliares

retorna o maior valor entre dois inteiros


``` c
 #define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

```

---

retorna a altura de um nó

``` c
 int height(No *root) {
    if (root == NULL)
        return 0;
    return max(height(root->esq), height(root->dir)) + 1;
}
```

---

retorna o numero de colunas para a matriz de impressão

``` c
     int getcol(int h) {
    if (h == 1)
        return 1;
    return getcol(h - 1) + getcol(h - 1) + 1;
}
```

---

imprime a arvore em forma de matriz adaptado de um código em C++ do [geeksforgeeks](https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/)

``` c
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
```
