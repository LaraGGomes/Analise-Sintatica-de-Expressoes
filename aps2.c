#include "aps2.h"

/*
    Protótipos das funções
*/

no* criarNo(char *expressao);
int enqueue(fila* f, char *expressao);
int dequeue(fila* f);
char * first(fila f);
int taVazia(fila f);
void mostrarFila(no *f);
void destruirFila(fila *f);

int E(fila *f,char **p);
int Op(fila* f, char **p);
void mostrarDerivacao (int tam, fila *f);

int main() {

    fila f;
    f.fim = NULL;
    f.in = NULL;

    char *cadeia;
    int tam;

    printf("Insira a cadeia a ser analisada: ");
    fgets(cadeia, 50, stdin);

    strip(cadeia, strlen(cadeia));

    tam = strlen(cadeia);

    char *p = cadeia;

    if (E(&f, &p) && p == &cadeia[tam]) {
        printf("Cadeia validada, segue a sua derivacao mais a esquerda.\n");
        mostrarDerivacao(tam, &f);

    }

    else printf("Cadeia invalida para essa gramatica.\n");

    destruirFila(&f);

    return 0;
}
