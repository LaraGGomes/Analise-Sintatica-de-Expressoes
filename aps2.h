#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    char l;
    struct no* prox;
} no;
typedef struct fila{
    no* in;
    no* fim;

} fila;

/*
    Funções básicas para no e fila
*/

no* criarNo(char letra);
int enqueue(fila* f, char letra);
int dequeue(fila* f);
char last(fila f);
int taVazia(fila f);
void mostrarDerivacao(fila f);

no* criarNo(char letra) {
    no *novo;
    novo = (no*)malloc(sizeof(no));
    if (!novo) {
        printf("Erro ao mallocar nó\n");
        return NULL;
    }

    novo->l = letra;
    novo->prox = NULL;
    return novo;
}

int enqueue(fila *f, char letra) {
    no* novo = criarNo(letra);

    if (!novo) return 0;

    // fila vazia
    if (f->in == NULL) {
        f->in = novo;
        f->fim = novo;

        return 1;
    }

    f->fim->prox = novo;
    f->fim = novo;

    return 1;
}

int dequeue(fila *f) {
    // fila vazia
    if (taVazia(*f)) {
        return 0;
    }

    // elemento único
    if (f->in == f->fim) {
        free(f->in);
        f->in = NULL;
        f->fim = NULL;

        return 1;
    }

    no *aux = f->in->prox;
    free(f->in);
    f->in = aux;
    return 1;
}

char last(fila f) {
    // fila vazia
    if (taVazia(f)) {
        printf("Nao tem elemento a ser mostrado\n");
        return '#';
    }

    return f.fim->l;
}

int taVazia(fila f) {
    if (f.in == NULL) return 1;
    return 0;
}

/*
    Funções da gramática
*/

int E(fila *f,char *p);
int Op(char *p);

int E(fila *f,char *p) {
    
}