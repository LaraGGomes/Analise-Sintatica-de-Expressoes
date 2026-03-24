#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    char *exp;
    struct no* prox;
} no;
typedef struct fila{
    no* in;
    no* fim;

} fila;

/*
    Funções básicas para no e fila
*/

no* criarNo(char *expressao);
int enqueue(fila* f, char *expressao);
int dequeue(fila* f);
char * first(fila f);
int taVazia(fila f);
void mostrarDerivacao(fila *f);

no* criarNo(char *expressao) {
    no *novo;
    novo = (no*)malloc(sizeof(no));
    if (!novo) {
        printf("Erro ao mallocar nó\n");
        return NULL;
    }

    novo->exp = expressao;
    novo->prox = NULL;
    return novo;
}

int enqueue(fila *f, char *expressao) {
    no* novo = criarNo(expressao);

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

char * first(fila f) {
    // fila vazia
    if (taVazia(f)) {
        printf("Nao tem elemento a ser mostrado\n");
        return "#";
    }

    return f.in->exp;
}

int taVazia(fila f) {
    if (f.in == NULL) return 1;
    return 0;
}

void destruirFila(fila *f) {
    if (taVazia(*f)) return;
    while (!taVazia(*f)) {
        dequeue(f);
    }
}

void mostrarDerivacao(fila *f) {
    if (taVazia(*f)) {
        printf("\nTa vazia\n");
        return;
    }

    printf("\nDerivação:\n");
    while (f->in != f->fim) {
        printf("%s -> ", first(*f));
        dequeue(f);
    }
    printf("%s", first(*f));
}

void derivacao (fila *f) {
    int i = 0, flag, aux;
    char final[200];    //mudar pra alocação dinamica dps
    printf("\nDerivação:\nE -> ");

    strcpy(final, first(*f));
    while (f->in != f->fim) {
        flag = 0;
        char *str = first(*f);

        for (int j = 0; str[j] != '\0'; j++) {
            if (final[j] == 'E') {
                flag = 1;
                i++;
                aux = j;
                break;
            }
            if (final[j] == 'O') {
                flag = 1;
                i+= 2;
                aux = j;
                break;
            }
        }
        // socorro
        if (flag) {
            dequeue(f);
            char *prox = first(*f);

            printf("%s -> ", str);
            //printf("%s -> ", prox);

            for (int j = 0; prox[j] != '\0'; j++) {
                final[i] = prox[j];
                i++;
            }

            for (++aux; str[aux] != '\0'; aux++) {
                final[i] = str[aux];
                i++;
            }

            printf("%s -> ", final);

            dequeue(f);
        }

        else break;
    }
}

/*
    Funções da gramática
*/

int E(fila *f,char **p);
int Op(fila* f, char **p);
char E2[] = "(E Op E)";

int E(fila *f,char **p) {

    if (**p == 'a') {
        // colocar expressão na fila
        if (!enqueue(f, "a")) return 0; // se n der pra inserir fudeu

        // próximo caractere
        ++(*p);
        return 1;
    }

    if (**p == '(') {
        if (!enqueue(f, "(E Op E)")) return 0;

        *p = (*p)+1;
        if (!E(f, p)) return 0;

        if (!Op(f, p)) return 0;

        if (!E(f, p)) return 0;

        if(**p == ')') {
            ++(*p);
            return 1;
        }
    }

    return 0;
}

int Op(fila* f, char **p) {

    if (**p == '+' || **p == '*' || **p == '/' || **p == '-') {
        if (**p == '+') {
            if (!enqueue(f, "+")) return 0;
        }

        if (**p == '*') {
            if (!enqueue(f, "*")) return 0;
        }
        if (**p == '/') {
            if (!enqueue(f, "/")) return 0;
        }
        if (**p == '-') {
            if (!enqueue(f, "-")) return 0;
        }

        ++(*p);
        return 1;
    }

    return 0;
}