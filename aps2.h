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
void mostrarFila(no *f);
void destruirFila(fila *f);

/*
    Funções da gramática
*/

int E(fila *f,char **p);
int Op(fila* f, char **p);
void mostrarDerivacao (int tam, fila *f);

void strip(char* s, int tam);

// variável global de expressão pra facilitar inserção
char E2[] = "(E Op E)";

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
        return "#";
    }

    return f.in->exp;
}

int taVazia(fila f) {
    if (f.in == NULL) return 1;
    return 0;
}

void mostrarFila(no *f) {
    if (!f) return;

    printf("%s, ", f->exp);

    mostrarFila(f->prox);
}

void destruirFila(fila *f) {
    if (taVazia(*f)) return;
    while (!taVazia(*f)) {
        dequeue(f);
    }
}

int E(fila *f,char **p) {

    if (**p == 'a') {
        // colocar expressão na fila
        if (!enqueue(f, "a")) return 0;

        // próximo caractere
        ++(*p);
        return 1;
    }

    if (**p == '(') {
        if (!enqueue(f, E2)) return 0;

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

void mostrarDerivacao (int tam, fila *f) {
    int i, flag, aux;
    char saida[3*tam];          // tamanho da entrada multiplicado (considerando espaços e Op's)

    printf("\nDerivacao:\nE -> ");

    strcpy(saida, first(*f));   // a saida é inicialmente o primeiro valor inserido na fila

    while (!taVazia(*f)) {
        flag = 0;               // vai ser 1 se ainda houverem símbolos não-terminais na string
        char str[3*tam];        // string auxiliar
        strcpy(str, saida);

        // checagem de símbolos não-terminais
        for (i = 0; saida[i] != '\0'; i++) {
            if (saida[i] == 'E') {
                flag = 1;
                break;
            }
            if (saida[i] == 'O') {
                flag = 2;       // diferente por causa do caractere a mais (p)
                break;
            }
        }

        // se tem flag, ainda precisa de derivação
        if (flag) {
            
            // se a saida for igual ao primeiro da fila, significa que estamos na primeira iteração do loop
            if (!strcmp(saida, first(*f))) {
                dequeue(f);                     // tem que retirar o primeiro da fila para acessar o que vai ser inserido 
                printf("%s -> ", saida);        // e printar a primeira derivação
            }
            aux = i+1;                          // auxiliar guarda posição em que foi encontrada a variável +1 (espaço em branco de onde vamos voltar a imprimir a string, pulando a variável)

            char *prox = first(*f);             // próxima derivação, que vai ser inserida

            // inserindo a derivação da string
            for (int j = 0; prox[j] != '\0'; j++) {
                saida[i] = prox[j];
                i++;
            }

            if (flag == 2) aux++;               // flag = 2 é Op, o que significa que temos que pular uma posição a mais

            // reinserindo o restante da string pós variável
            for (int j = aux; str[j] != '\0'; j++) {
                saida[i] = str[j];
                i++;
            }

            // eliminando caractere extra no final da string saida resultado do pulo de Op
            if (flag == 2) saida[i] = '\0';

            dequeue(f);                         // próximo elemento da fila

            // se não houver elemento no topo (fila vazia), a saida atual é a final e a derivação vai acabar na próxima iteração
            if (!taVazia(*f))
                printf("%s -> ", saida);       // se não, imprime a saida com a setinha e segue a derivação
        }

        // string só está composta por símbolos terminais, pode acabar
        else break;
    }
    printf("%s", saida);
}

void strip(char* s, int tam) {
    for (int i = 0; i < tam; i++) {
        if (s[i] == ' ') {
            for (int j = i; j < tam; j++) {
                s[j] = s[j+1];
            }
            
            tam--;
        }
        if (s[i] == ' ') i--;
    }
    
    s[tam-1] = '\0';
}
