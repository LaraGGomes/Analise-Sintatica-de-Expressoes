#include "aps2.h"

/*
    Protótipos das funções
*/

no* criarNo(char *expressao);
int enqueue(fila* f, char *expressao);
int dequeue(fila* f);
char * last(fila f);
int taVazia(fila f);
void mostrarDerivacao(fila *f);


int main() {

    fila f;
    f.fim = NULL;
    f.in = NULL;

    char s[] = "(a*(a+a))";
    char s1[] = "(a+a)";

    char* p = s1;

    if (E(&f, &p)) printf("Yiiipee\n");
    else printf("whompwhomp\n");

    // mostrarDerivacao(&f);
    // destruirFila(&f);
    // mostrarDerivacao(&f);
    derivacao(&f);
    destruirFila(&f);

    return 0;
}



