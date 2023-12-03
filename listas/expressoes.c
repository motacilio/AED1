#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct caracter Caracter;
typedef struct pilha Pilha;

struct caracter{
    char caracter;
    Caracter *prox;
};

struct pilha{
    Caracter *topo;
};

Pilha *Pilha_criar(){
    Pilha *p = (Pilha *) calloc(1, sizeof(Pilha));
    p->topo = NULL;
    return p;
}

void Pilha_empilhar(Pilha *p, char c){
    Caracter *novoCaracter = (Caracter *) malloc(sizeof(Caracter));
    if(novoCaracter == NULL){
        printf("Erro ao alocar memoria para novo caracter\n");
    } else {
        novoCaracter->caracter = c; 
        novoCaracter->prox = p->topo;
        p->topo = novoCaracter;
    }
}


char Pilha_desempilhar(Pilha *p){
    if(p->topo == NULL){
        return '0';
    } 
    char caracter_removido = p->topo->caracter;
    Caracter *temp = p->topo;
    p->topo = p->topo->prox;
    free(temp);

    return caracter_removido;
}

int ehFechamentoCorreto(char abertura, char fechamento){
    if(abertura == '(' && fechamento == ')'){
        return 1; 
    } else if(abertura == '[' && fechamento == ']'){
        return 1;
    } else if(abertura == '{' && fechamento == '}'){
        return 1;
    }

    return 0;
}

int ehExpressaoBalanceada(char expressao[]){
    int i = 0;
    Pilha *p = Pilha_criar();  

    while(expressao[i] != '\0'){
        if(expressao[i] == '(' || expressao[i] == '[' || expressao[i] == '{'){
            Pilha_empilhar(p, expressao[i]);
        } else if(expressao[i] == ')' || expressao[i] == ']' || expressao[i] == '}'){
            char abertura = Pilha_desempilhar(p);
            if(!ehFechamentoCorreto(abertura, expressao[i])){
                return 0;
            }
        }
        i++;
    }     

    if(p->topo != NULL){
        return 0;
    } else{
        return 1;
    }
}


int main(){
    int i, t; scanf("%d", &t);

    char **respostas = (char **) malloc(sizeof(char *) * t);
    for(i = 0; i < t; i++){
        respostas[i] = (char *) malloc(sizeof(char) * 11);
    }    
    
    for(i = 0; i < t; i++){
        char expressao[1001];
        scanf(" %1001[^\n]", expressao);

        if(ehExpressaoBalanceada(expressao)){
            strcpy(respostas[i], "bem-formada"); 
        } else{
            strcpy(respostas[i], "mal-formada");
        }
    }
    
    for(i = 0; i < t; i++){
        printf("%s\n", respostas[i]);
    }

}