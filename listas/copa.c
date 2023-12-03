#include <stdio.h>
#include <stdlib.h>
#define SUCESSO 1
#define FALHA 0

// -------------------------------------
typedef struct pessoa Pessoa;
typedef struct fila Fila;
Fila *Fila_criar();
Pessoa *Pessoa_criar(int senha);
void Fila_adicionar_fim(Fila *F, Pessoa *pessoa);
void Fila_remover(Fila *F, int senha);
void Fila_imprimir(Fila *F);
//-------------------------------------

struct pessoa{
    int senha;
    Pessoa *prox;
};

struct fila{
    Pessoa *begin;
};

Fila *Fila_criar(){
    Fila *F = (Fila *) calloc(1, sizeof(Fila));
    F->begin = NULL;

    return F;
}

Pessoa *Pessoa_criar(int senha){
    Pessoa *p = (Pessoa *)calloc(1, sizeof(Pessoa));
        p->senha = senha;
        p->prox = NULL;

        return p;
}

void Fila_adicionar_fim(Fila *F, Pessoa *pessoa){
    if(F->begin == NULL){
        F->begin = pessoa;
    } else{ 
        Pessoa *pAtual = F->begin;
        while(pAtual->prox != NULL){
            pAtual = pAtual->prox;
        }
        pAtual->prox = pessoa;
    }
}

void Fila_remover(Fila *F, int senha) {
    Pessoa *anterior = NULL;
    Pessoa *atual = F->begin;

    while (atual != NULL && atual->senha != senha) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        if (anterior == NULL) {
            // Se a pessoa a ser removida está no início da fila
            F->begin = atual->prox;
        } else {
            // Se a pessoa a ser removida está no meio ou no final da fila
            anterior->prox = atual->prox;
        }

        free(atual);
    }
}


void Fila_imprimir(Fila *F){
    Pessoa *pAtual = F->begin;
    while(pAtual != NULL){
        printf("%d ", pAtual->senha);
        pAtual = pAtual->prox;
    }
}
//------------------------------------


int main(){
    
    Fila *fila = Fila_criar();
    int senha;
    int i, n = 0;; 
    while(n < 1 || n > 60000){
        scanf("%d", &n);
    }

    for(i = 0; i < n; i++){
        int senhaAtual; scanf("%d", &senhaAtual);
        Pessoa *pAtual = Pessoa_criar(senhaAtual);
        Fila_adicionar_fim(fila, pAtual);
    }   



    // quantidade de quem abandonou a fila
    int s; scanf("%d", &s);

    for(i = 0; i < s; i++){
        scanf("%d", &senha);
        Fila_remover(fila, senha);
    }

    Fila_imprimir(fila);

}

