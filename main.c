#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main()
{
    Arvore *arv = cria();

    arv->insere(arv, 10);
    arv->insere(arv, 12);
    arv->insere(arv, 13);
    arv->insere(arv, 11);
    arv->insere(arv, 5);
    arv->insere(arv, 1);
    arv->insere(arv, 14);
    arv->insere(arv, 10);
    arv->imprime(arv);
}