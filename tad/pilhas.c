 #include <stdlib.h>
 #include <stdio.h>
 #include <limits.h>

#define FALHA 0
#define SUCESSO 1
#define FALSE 0
#define TRUE 1
#define TOPO 1
#define BASE 0

// Arquivo.h

void opcoes(){
    printf("1. Criar uma pilha\n");
    printf("2. Verifica se uma pilha eh vazia\n");
    printf("3. Insere um elemento em uma pilha\n");
    printf("4. Remove um elemento de uma pilha\n");
    printf("5. Retorna o tamanho de uma pilha\n");
    printf("6. Verifica se duas pilhas sao iguais\n");
    printf("7. Exibe os elementos de uma pilha\n");
    printf("8. Copia uma pilha P1 para uma P2\n");
    printf("0. Para o programa\n");
    printf("99 - exibe as opcoes novamente\n");
}

typedef struct pilha Pilha;

int create(Pilha *P);
int isEmpty(Pilha *P);
int push(Pilha *P, int x);
unsigned long int pop(Pilha *P);
long int size(Pilha *P);
int isEqual(Pilha *P1, Pilha *P2);
void show(Pilha *P, int ordem);
int copy(Pilha *P1, Pilha *P2);


// Arquivo.c

struct pilha{
    long int *elementos;
    int topo;
};


int create(Pilha *P){
    if(P == NULL){
        return FALHA;
    }
    P->elementos = (long int *)calloc(1000000, sizeof(long int));
    if (P->elementos == NULL) {
        return FALHA;
    }
    P->topo = -1;
    return SUCESSO;
}

int isEmpty(Pilha *P){
   if(P == NULL){
        return 5;
    }
    return P->topo == -1;
}

int push(Pilha *P, int x){
    if(P == NULL || P->elementos == NULL || (x > LONG_MAX && x < LONG_MIN) || P->topo == 999999){
        return FALHA;
    }
    P->elementos[++P->topo] = x;
    return SUCESSO;
    }

unsigned long int pop(Pilha *P){
    if(P == NULL || P->topo == -1){
        return FALHA;
    }
    P->topo--;
    return SUCESSO;
}

long int size(Pilha *P){
    return P->topo+1; 
}

int isEqual(Pilha *P1, Pilha *P2){
    if(P1->topo == P2->topo){
        for(int i = 0; i <= P1->topo; i++){
            if(P1->elementos[i] != P2->elementos[i]){
                return FALSE;
            }
        }
        return TRUE;
    }
    return FALSE;
}

void show(Pilha *P, int ordem){
    if(P->topo == -1){
        printf("PILHA VAZIA\n");
    } else if(ordem == TOPO){
        printf("Elementos:\n");
        for(int i = 0; i <= P->topo; i++){
            printf("%ld\n", P->elementos[i]);
        }
    } else if(ordem == BASE){
        printf("Elementos:\n");
        for(int i = P->topo; i >= 0; i--){
            printf("%ld\n", P->elementos[i]);
        } 
    }    
}

int copy(Pilha *P1, Pilha *P2){
    if(P1 == NULL || P2 == NULL || (P1->topo + P2->topo) == 999999){
        return FALHA;
    } 
    for(int i = 0; i <= P1->topo; i++){
        push(P2, P1->elementos[i]);
    }
    return SUCESSO;
}

// Corpo principal
 int main(){
    opcoes();

    Pilha *pilhas = NULL;
    unsigned int numPilhas = 0;
    unsigned int pilha, pilha2;
    int opcao = -1;
    
    while(opcao != 0){
        printf("Digite sua opcao:\n");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Pilha *novaPilha = (Pilha *)realloc(pilhas, (numPilhas + 1) * sizeof(Pilha));

            if (novaPilha == NULL) {
                printf("Erro ao alocar pilha\n");
            } 
            else {
                pilhas = novaPilha;

                if (create(&pilhas[numPilhas]) == FALHA) {
                    printf("Erro ao criar a pilha\n");
                } else {
                    numPilhas++;
                    printf("Pilha %u criada com sucesso\n", numPilhas);
                }
            }

        } else if (opcao == 2){
            printf("Digite a pilha: \n");
            scanf("%u", &pilha);
            pilha--;

            int resultado = isEmpty(&pilhas[pilha]);

            if(resultado == TRUE){
                printf("A pilha eh vazia\n");
            } else if(resultado == FALSE){
                printf("A pilha nao eh vazia\n");
            } 

        } else if(opcao == 3){
            printf("Digite a pilha: \n");
            scanf("%u", &pilha);
            pilha--;
            printf("Digite o elemento: \n");
            int elemento; scanf("%d", &elemento);

            int resultado = push(&pilhas[pilha], elemento);
            if(resultado == SUCESSO){
                printf("Elemento inserido com sucesso\n");
            } else{
                printf("Falha ao inserir elemento\n");
            }
        } else if(opcao == 4){
            printf("Digite a pilha: \n");
            scanf("%u", &pilha);
            pilha--;

            int resultado = pop(&pilhas[pilha]);
            if(resultado == SUCESSO){
                printf("Ultimo elemento excluido com sucesso\n");
            } else{
                printf("Erro ao excluir\n");
            }
        } else if(opcao == 5){
            printf("Digite a pilha: \n");
            scanf("%u", &pilha); pilha--;

            long int tamanho = size(&pilhas[pilha]);
            if(tamanho > 0){
                printf("O tamanho da pilha eh: %ld\n", tamanho);
            } else{
                printf("A pilha esta vazia\n");
            }

        } else if(opcao == 6){
            printf("Digite a pilha: \n");
            scanf("%u", &pilha); pilha--;
            printf("Digite a segunda pilha:\n");
            scanf("%u", &pilha2); pilha2--;

            int resultado = isEqual(&pilhas[pilha], &pilhas[pilha2]);
            if(resultado == SUCESSO){
                printf("As pilhas sao iguais\n");
            } else{
                printf("As pilhas sao diferentes\n");
            }
        } else if(opcao == 7){
            printf("Digite a pilha: \n");
            scanf("%u", &pilha); pilha--;
            printf("Digite a ordem (1. TOPO - 0. BASE): \n");
            int ordem; scanf("%d", &ordem);
            if(ordem != 1 && ordem != 0){
                printf("Erro, Digite 1 ou 0 para a ordem\n");
            }

            show(&pilhas[pilha], ordem);

        } else if(opcao == 8){
            printf("Digite a pilha: \n");
            scanf("%u", &pilha); pilha--;
            printf("Digite a segunda pilha:\n");
            scanf("%u", &pilha2); pilha2--;

            int resultado = copy(&pilhas[pilha], &pilhas[pilha2]);
            if(resultado == FALHA){
                printf("Copia mal-sucedida\n");
            } else{
                printf("Copia bem sucedida\n");
            }
        }
        else if(opcao == 0){
            for (unsigned int i = 0; i < numPilhas; i++) {
                free(pilhas[i].elementos);
            }
            free(pilhas);
            break;
        } else if(opcao == 99){
            opcoes();
        }
    }

  

 }