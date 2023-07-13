#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>

#define M 2
#define MM (2 * M)

typedef int TChave;

int vetor[100];
char vetorEntrada[100][260];

typedef struct {
    TChave Chave;
    /* outros compomentes */
} TItem;

typedef int TIndice;

typedef struct SNo *TArvoreB;

typedef struct SNo {
    TItem Item[MM];
    TArvoreB Pagina[MM + 1];
    TIndice n;
} TNo;

/* Estrutura para passar pra cima */
typedef struct{
    TItem item;
    TArvoreB pagina;
} TInfo;

typedef TInfo* PInfo;

int EhInterno(TArvoreB No)
{
    return (No != NULL) && (No->Pagina[0] != NULL);
}

int EhExterno(TArvoreB No)
{
    return (No != NULL) && (No->Pagina[0] == NULL);
}

TArvoreB Inicializa()
{
    return NULL;
}

/* Inicializa um novo no com o elemento dado */
TArvoreB Empacotador(TItem x){
    TArvoreB pacote;

    pacote= (TArvoreB) malloc(sizeof(TNo));
    pacote->Item[0] = x;
    pacote->n = 1;

    return pacote;
}

void InsereNo(TArvoreB raiz, PInfo info, TIndice i);
void InsereNo2(TArvoreB raiz, PInfo info);

/* Divide uma pagina em duas */
void Divide(TArvoreB raiz, TItem x, TIndice indice, PInfo* info){
    TArvoreB novo;
    int i, j;

    novo = (TArvoreB) malloc(sizeof(TNo));
    (*info)->pagina = novo;
    novo->n = 0;

    /* Transfere metade das paginas/itens para o no novo */
    for(i=M, j=0; i<MM && j<M; i++, j++){

        /* Elementos para a nova pagina */
        novo->Item[j] = raiz->Item[i];
        novo->Pagina[j+1] = raiz->Pagina[i+1];

        /* Ajusta os contadores */
        novo->n++;
        raiz->n--;


    }

    /* Vamos inserir o novo item para decidir qual par promover */
    if(indice < M){
        InsereNo2(raiz, *info);

        /* Seleciona o item e coloca no lugar de promocao */
        (*info)->item = raiz->Item[raiz->n-1];
        raiz->n--;
    }
    else{
        InsereNo2(novo, *info);

        /* Seleciona o item para promocao */
        (*info)->item = novo->Item[0];

        /* Puxa todo mundo pra tras */
        novo->n--;
        for(i=0; i<=novo->n; i++){
            novo->Item[i] = novo->Item[i+1];
            novo->Pagina[i] = novo->Pagina[i+1];
        }

    }

    /* Ajusta o primeiro filho do novo no para o ultimo
     * do velho no */
    novo->Pagina[0] = raiz->Pagina[raiz->n];
}

/* Retorna o ponteiro para onde o no foi encontrado
 * ou NULL caso nao seja encontrado */
TArvoreB Pesquisa(TArvoreB Raiz, TChave x){
    int i;

    /* Se a arvore for nula */
    if(Raiz == NULL)
        return NULL;

    for(i=0; i<Raiz->n; i++){

        if(Raiz->Item[i].Chave == x)
            return Raiz;

        /* Se o elemento for menor do que o analisado */
        if(Raiz->Item[i].Chave > x)
            return Pesquisa(Raiz->Pagina[i], x);
    }

    /* Verificamos se o elemento pode estar na ultima pagina
     * Se chegar aqui, i = (*pRaiz)->n-1 */
    if(x > Raiz->Item[i].Chave && Raiz->Pagina[i+1] != NULL){
        return Pesquisa(Raiz->Pagina[Raiz->n], x);
    }

    /* Pesquisa sem sucesso */
    return NULL;
}

/* Insere quando nao sabemos o indice onde devemos inserir */
void InsereNo2(TArvoreB raiz, PInfo info){
    int j;

    for(j=0; j<raiz->n && raiz->Item[j].Chave < info->item.Chave; j++);

    /* Se o item ja estiver inserido */
    if(raiz->Item[j].Chave == info->item.Chave)
        return;

    /* Se tivermos achado o indice onde colocar */
    InsereNo(raiz, info, j);
}

/* Insere dentro de um no que tem espaco */
void InsereNo(TArvoreB raiz, PInfo info, TIndice i){
    int j;

    /* Desloca os necessarios elementos para frente */
    for(j=raiz->n; j>i; j--){
        raiz->Item[j] = raiz->Item[j-1];
        raiz->Pagina[j] = raiz->Pagina[j-1];
    }

    /* Aumenta o numero de itens neste no */
    raiz->n++;

    /* Insere o elemento na posicao liberada */
    raiz->Item[i] = info->item;
    raiz->Pagina[i] = info->pagina;
}

/* Insere com promocao */
int InsereRec(TArvoreB raiz, TItem x, PInfo* info){
    int i, j, k;

    /* Se atingiu a base da arvore */
    if(raiz == NULL){
        (*info) = (PInfo) malloc(sizeof(TInfo));
        (*info)->item = x;
        (*info)->pagina = NULL;
        return 1;
    }

    /* Acha a posicao onde deve inserir o elemento novo */
    for(i=0; i<raiz->n && raiz->Item[i].Chave < x.Chave; i++);

    /* Chegamos no ponto de pesquisa com sucesso */
    if(raiz->Item[i].Chave == x.Chave)
        return 0;


    /* Insere e ve se o nivel de baixo aumentou */
    if(InsereRec(raiz->Pagina[i], x, info)){

        /* Se houver espaco na pagina */
        if(raiz->n < MM){
            /* Insere neste no */
            InsereNo(raiz, *info, i);
            return 0;
        }
        else{
            /* Se a pagina estiver lotada, divida */
            Divide(raiz, x, i, info);
            return 1;
        }
    }
}

/* Insere na arvore */
void Insere(TArvoreB *pRaiz, TItem x){
    int i;
    TArvoreB aux;
    PInfo info = (PInfo) malloc(sizeof(TInfo));

    /* Se a arvore for nula */
    if(*pRaiz == NULL){
        *pRaiz = Empacotador(x);
    }
    else{
        /* Encontro o indice onde deveria inserir o item neste no */
        for(i=0; i<(*pRaiz)->n && (*pRaiz)->Item[i].Chave < x.Chave; i++);

        /* Se achamos um item igual */
        if((*pRaiz)->Item[i].Chave == x.Chave){
            return;
        }

        /* Seleciona a pagina onde deve ser feita a insercao */
        aux = (*pRaiz)->Pagina[i];

        /* Faz a insercao propriamente dita */
        if(InsereRec(aux, x, &info)){

            /* Se houver espaco na raiz */
            if((*pRaiz)->n < MM){
                InsereNo((*pRaiz), info, i);
            }

            /* Divide a raiz */
            else{
                aux = *pRaiz;

                /* Divide a raiz e acerta a galera que deve ser promovida */
                Divide((*pRaiz), x, i, &info);

                /* Recriamos a raiz */
                *pRaiz = Empacotador(info->item);
                (*pRaiz)->Pagina[0] = aux;
                (*pRaiz)->Pagina[1] = info->pagina;
            }
        }
    }
}

void Imprime(TArvoreB No)
{
    TIndice i;

    if (No != NULL) {
        printf("(");
        for (i = 0; i < No->n; i++) {
            Imprime(No->Pagina[i]);
            printf("C%s", No->Item[i].Chave);
        }
        Imprime(No->Pagina[No->n]);
        printf(")");
    }
    else
        printf("()");
}


void Carrega(TArvoreB *pNo,int n)
{
    int i;
    TItem x;

    for (i = 0; i < n ; i++)
    {
        printf("Leu dentro: ");
        x.Chave = (vetor[i]+1);
        printf("%s",vetor[i]+1);
        printf("--- %i\n",x.Chave);

        Insere(pNo, x);
        /*Imprime(*pNo);*/
    }
}

void Libera(TArvoreB *pNo)
{
    TArvoreB No;
    TIndice i;

    No = *pNo;
    if (No != NULL)
    {
        for (i = 0; i <= No->n; i++)
            Libera(&No->Pagina[i]);
        free(No);
        (*pNo) = NULL;
    }
}

int main()
{
    int tamChave = 0;
int *dir;
    struct dirent *ent;
    if ((dir = opendir("C:\\Users\\jabir\\Desktop\\")) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            if(strcmp(ent->d_name,".") != 0 && strcmp(ent->d_name,"..") != 0)
            {
                strcpy(vetorEntrada[tamChave], ent->d_name);
                vetor[tamChave] = (int *)(vetorEntrada[tamChave]);
                /*printf ("%s\n", ent->d_name);*/
                tamChave = tamChave + 1;
            }
        }
        closedir (dir);
    }
    else
    {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }

printf("Tamanho %i \n",tamChave);

    TArvoreB Raiz;
     TItem x;

     Raiz = Inicializa();
     Carrega(&Raiz,tamChave);
     Libera(&Raiz);

    return 0;
}