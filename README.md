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
