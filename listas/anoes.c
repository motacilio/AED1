#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cor Cor;
typedef struct anao Anao;
typedef struct fila Fila;
typedef struct foto Foto;

Anao *Anao_criar(int cor);
Fila *Fila_criar();
void Fila_adicionar(Fila *f, Anao *anao);
Cor *Cor_contar(Fila *fila);

struct anao {
    int cor;
    Anao *prox;
};

struct fila {
    Anao *inicio;
};

struct cor {
    int cor;
    int contagem;
};

struct foto {
    char qualidade[20];
    int cor;
};

int main() {
    int j, i, t, n, c;

    scanf("%d", &t);

    Foto ***lista_listaFotos = (Foto ***)calloc(t, sizeof(Foto **));
    int *lista_m = (int *)calloc(t, sizeof(int));

    // Loop externo para iterar sobre cada caso
    for (j = 0; j < t; j++) {
        scanf("%d %d", &n, &c);

        Fila *f = Fila_criar();

        for (i = 0; i < n; i++) {
            int corI;
            scanf("%d", &corI);
            Anao *a = Anao_criar(corI);
            Fila_adicionar(f, a);
        }

        int m;
        scanf("%d", &m);
        lista_m[j] = m;

        lista_listaFotos[j] = (Foto **)calloc(m, sizeof(Foto *));

        // Loop interno para iterar sobre cada foto dentro do caso
        for (i = 0; i < m; i++) {
            int a, b;
            scanf("%d %d", &a, &b);

            Fila *fila_foto = Fila_criar();
            Anao *aux = f->inicio;
            int k;
            for (k = 1; k <= b; k++) {
                if (k >= a) {
                    Anao *novo_anao = Anao_criar(aux->cor);
                    Fila_adicionar(fila_foto, novo_anao);
                }
                aux = aux->prox;
            }

            Cor *cores_foto = Cor_contar(fila_foto);

            int metade = (b - a + 1) / 2 + 1;
            int cor_predominante = 0;
            int corP_contagem = 0;

            for (k = 1; k <= c; k++) {
                if (cores_foto[k].contagem > corP_contagem) {
                    corP_contagem = cores_foto[k].contagem;
                    cor_predominante = cores_foto[k].cor;
                }
            }

            lista_listaFotos[j][i] = (Foto *)malloc(sizeof(Foto));

            if (corP_contagem >= metade) {
                lista_listaFotos[j][i]->cor = cor_predominante;
                strcpy(lista_listaFotos[j][i]->qualidade, "bonita");
            } else {
                lista_listaFotos[j][i]->cor = 0;
                strcpy(lista_listaFotos[j][i]->qualidade, "feia");
            }

            free(fila_foto);
        }

        // Liberar a memória alocada para a fila principal
        Anao *atual = f->inicio;
        Anao *prox = NULL;
        while (atual != NULL) {
            prox = atual->prox;
            free(atual);
            atual = prox;
        }

        free(f);
    }

    // Imprimir os resultados
    for (j = 0; j < t; j++) {
        for (i = 0; i < lista_m[j]; i++) {
            if (lista_listaFotos[j][i]->cor != 0) {
                printf("%s %d\n", lista_listaFotos[j][i]->qualidade, lista_listaFotos[j][i]->cor);
            } else {
                printf("feia\n");
            }

            // Liberar a memória alocada para cada foto
            free(lista_listaFotos[j][i]);
        }

        // Liberar a memória alocada para a lista de fotos
        free(lista_listaFotos[j]);
    }

    // Liberar a memória alocada para o array que armazena o número de fotos em cada caso
    free(lista_m);

    // Liberar a memória alocada para a lista de listas de fotos
    free(lista_listaFotos);

    return 0;
}


Anao *Anao_criar(int cor) {
    Anao *a = (Anao *)calloc(1, sizeof(Anao));
    a->cor = cor;
    a->prox = NULL;
    return a;
}

Fila *Fila_criar() {
    Fila *f = (Fila *)calloc(1, sizeof(Fila));
    f->inicio = NULL;
    return f;
}

void Fila_adicionar(Fila *f, Anao *anao) {
    if (f->inicio == NULL) {
        f->inicio = anao;
    } else {
        Anao *q = f->inicio;
        while (q->prox != NULL) {
            q = q->prox;
        }
        q->prox = anao;
    }
}

Cor *Cor_contar(Fila *fila) {
    Cor *cores = (Cor *)calloc(10001, sizeof(Cor));

    Anao *aux = fila->inicio;
    while (aux != NULL) {
        cores[aux->cor].contagem++;
        cores[aux->cor].cor = aux->cor;
        aux = aux->prox;
    }

    return cores;
}
