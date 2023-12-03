#include <stdio.h>
#include <stdlib.h>

typedef struct caracter Caracter;
typedef struct pilha Pilha;

struct caracter {
    char caractere;
    Caracter *prox;
};

struct pilha {
    Caracter *topo;
};

Pilha *Pilha_criar() {
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro: falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    p->topo = NULL;
    return p;
}

void Pilha_adicionar(Pilha *pilha, char caracter) {
    Caracter *novoCaracter = (Caracter *)malloc(sizeof(Caracter));
    if (novoCaracter == NULL) {
        printf("Erro: falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoCaracter->caractere = caracter;
    novoCaracter->prox = pilha->topo;
    pilha->topo = novoCaracter;
}

char Pilha_remover(Pilha *pilha) {
    if (pilha->topo == NULL) {
        return 0;
    }

    char caracterRemovido = pilha->topo->caractere;
    Caracter *remover = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(remover);

    return caracterRemovido;
}

int ehParFechado(char abertura, char fechamento) {
    if (abertura == '(' && fechamento == ')'){
        return 1;
    }
    return 0;
}

int identifica_formacao(char x[]) {
    int i = 0;
    Pilha *p = Pilha_criar();

    while (x[i] != '\0') {
        if (x[i] == '(') {
            Pilha_adicionar(p, x[i]);
        } else if (x[i] == ')') {
            char abertura = Pilha_remover(p);
            if (ehParFechado(abertura, x[i]) == 0) {
                return 0; // Parêntese fechado sem correspondente aberto
            }
        } 
        i++;
    }

    if (p->topo != NULL) {
        return 0; // Parêntese aberto sem correspondente fechado
    } else {
        return 1; // Expressão correta
    }
}

int main() {
    char expressao[1001];
    scanf(" %1000[^\n]", expressao);

    if (identifica_formacao(expressao)) {
        printf("correta\n");
    } else {
        printf("incorreta\n");
    }

    return 0;
}
