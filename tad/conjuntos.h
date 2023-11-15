typedef struct conjunto Conjunto;

void quicksort(int *, int, int);

int buscaBin(int *, int, int, int);

int criaConjunto(Conjunto *);

int conjuntoVazio(Conjunto *C);

int insereElementoConjunto(int, Conjunto *);

int excluirElementoConjunto(int, Conjunto *);

int tamanhoConjunto(Conjunto *);

int maior(int, Conjunto *);

int menor(int, Conjunto *);

int pertenceConjunto(int, Conjunto *);

int conjuntosIdenticos(Conjunto *, Conjunto *);

int subconjunto(Conjunto *, Conjunto *);

Conjunto complemento(Conjunto *, Conjunto *);

Conjunto uniao(Conjunto *, Conjunto *);

Conjunto interseccao(Conjunto *, Conjunto *);

Conjunto diferenca(Conjunto *, Conjunto *);

Conjunto conjuntoPartes(Conjunto *);

void mostraConjunto(Conjunto *, int);

int copiarConjunto(Conjunto *, Conjunto *);

int destroiConjunto(Conjunto *);