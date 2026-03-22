#include "aps2.h"

/*
    Funções básicas para no e fila
*/

no* criarNo(char letra);
int enqueue(fila* f, char letra);
int dequeue(fila* f);
char last(fila f);
int taVazia(fila f);
void mostrarDerivacao(fila f);


int main() {

    fila f;
    f.fim = NULL;
    f.in = NULL;

    char s[] = "(a*(a+a))";
    char s1[] = "(a+)";

    char* p = s;

    if (E(&f, &p)) printf("Yiiipee");
    else printf("whompwhomp");

    return 0;
}



