#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main()
{
    Arvore *arv = cria();

    arv->insere(arv, 10);
    arv->insere(arv, 20);
    arv->insere(arv, 21);
    arv->insere(arv, 5);
    arv->insere(arv, 16);
    arv->insere(arv, 18);
    arv->insere(arv, 17);
    arv->insere(arv, 24);
    arv->insere(arv, 1);
    arv->insere(arv, 26);

    No* result;
    if(arv->busca(arv, 1, &result)){
        printf("No encontrado\n");
        printf("%p -> %d\n\n", result, result->info);
    } else printf("No não encontrado\n\n\n");

    arv->imprime(arv);

    
    printf("\n\n\n\n");
    arv->remove(arv, 20);
    arv->imprime(arv);

}