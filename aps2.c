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
void mostrarDerivacao (char *s, fila *f);

int main() {

    fila f;
    f.fim = NULL;
    f.in = NULL;

    char s[] = "((a+a)*a)"; // depois fazer o tratamento de espaço com strip
    char s1[] = "(a+a)";
    char s2[] = "a";

    char* p = s2;

    if (E(&f, &p)) printf("Yiiipee\n");
    else printf("whompwhomp\n");

    mostrarFila(f.in);
    mostrarDerivacao(s, &f);
    destruirFila(&f);

    return 0;
}
