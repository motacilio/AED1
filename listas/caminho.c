#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct direcao Direcao;
typedef struct caminho Caminho;

struct direcao{
    char orientecao[20];
    char nomeRua[20];
    Direcao *prox;
};

struct caminho{
    Direcao *topo;
};

Caminho *Caminho_criar(){
    Caminho *novoCaminho = (Caminho *) malloc(sizeof(Caminho));
    novoCaminho->topo = NULL;
    return novoCaminho;
}

Direcao *Direcao_criar(char orientacao[], char rua[]){
    Direcao *dir = (Direcao *) malloc(sizeof(Direcao));
    strcpy(dir->orientecao, orientacao);
    strcpy(dir->nomeRua, rua);
    dir->prox = NULL;

    return dir;
}

void Caminho_add(Caminho *caminho, Direcao *direcao){
    direcao->prox = caminho->topo;
    caminho->topo = direcao;
}

void imprime(Caminho *caminho){
    if(caminho->topo == NULL){
        printf("Pilha vazia\n");
    } else{
        Direcao *aux = caminho->topo;
        while(aux != NULL){
            printf("%s\n", aux->orientecao);
            printf("%s\n", aux->nomeRua);
            aux = aux->prox;
        }
    }
}


int main(){

    Caminho *ida = Caminho_criar();

    char or[20];
    char rua[20];
    scanf(" %20[^\n] ", or);
    scanf(" %20[^\n]", rua);

    Direcao *new = Direcao_criar(or, rua);
    Caminho_add(ida, new);
    imprime(ida);
  
}