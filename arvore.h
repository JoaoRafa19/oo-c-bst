#ifndef arvore_h
#define arvore_h

#define true 1
#define false 0

typedef int bool;

typedef struct arvore Arvore;

typedef struct no No;
struct no
{
    int info;
    No *esq;
    No *dir;
};

struct arvore
{
    No *_raiz;
    /**
     * @brief Método de inserção recursiva na arvore
     * @param a nó raiz/atual a ser verificado
     * @param info valor a ser adicionado na arvore
     */
    void (*insere)(Arvore *, int);
    /**
     * @brief Realiza uma busca na arvore e retorna se o elemento existe ou não (true/false)
     * e pode retornaro Nó resultado pela varíavel
     * @param arv Referencia da arvore onde será realizada a busca
     * @param info Conteúdo a ser buscado
     * @param resultado endereço de referência para cópia de resultado de busca
     */
    bool (*busca)(Arvore *, int, No **);
    /**
     * @brief Método para remoção recursiva de um nó com a informação desejada
     * @param root Referencia do nó raiz ou nó interno a ser removido
     * @param info Informação contida no nó que deseja remover
     */
    void (*remove)(Arvore *, int);
    /**
     * @brief Impressão por método de matriz da arvore
     * @param tree Nó raiz da arvore a ser impressa
     */
    void (*imprime)(Arvore *);
};

Arvore *cria();

#endif