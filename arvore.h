#ifndef arvore_h
#define arvore_h

#define true 1
#define false 0

typedef int bool;

typedef struct arvore Arvore;


typedef struct no  No;
struct no {
    int info;
    No* esq;
    No* dir;
};

struct arvore {
    No *_raiz;
    void(*insere)(Arvore* , int );
    bool(*busca)(Arvore* , int );
    void(*remove)(Arvore* , int );
    void(*imprime)(Arvore* );
};

Arvore* cria();

#endif