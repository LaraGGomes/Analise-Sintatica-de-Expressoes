typedef struct no{
    char l;
    struct no* nxt;
} no;
typedef struct fila{
    no* c;
    no* f;

} fila;

/*
    Funções básicas para no e fila
*/

no* criarNo(char letra);
int enqueue(fila** f, char letra);
int dequeue(fila** f);
char last(fila* f);
int taVazia(fila* f);
void mostrarDerivacao(fila* f);