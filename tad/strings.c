#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCESSO 1
#define FALHA 0
#define IGUAL 0
#define MENOR -1
#define MAIOR 1
/*
---------------------------------------------------------------------------
ARQUIVO.h
--------------------------------------------------------------------------*/
typedef struct texto Texto;

void opcoes();

//1 
Texto * criarTexto (char * t);
//2 
void liberarTexto (Texto * t);
//3 
unsigned int tamanhoTexto (Texto * t);
//4 
char * obterTexto (Texto * t);
//5
void mostrarTexto (Texto *t, unsigned int colunas);
//6
Texto * copiarTexto (Texto * t);
//7
void substituirTexto (Texto * t, char * alteracao);
//8
Texto * concatenarTextos (Texto * t1, Texto * t2);
//9
char * obterSubtexto (Texto * t, unsigned int inicio, unsigned int tamanho); 
//10
unsigned int encontrarSubtexto (Texto * t, char * subtexto, unsigned
int ocorrencia);
//11
int compararTextos (Texto * t1, Texto * t2); 

/*
---------------------------------------------------------------------------
ARQUIVO.c
--------------------------------------------------------------------------*/ 
struct texto{
    char *conteudo;
};
//1
Texto *criarTexto(char *t) {
    Texto *novoTexto = (Texto *)malloc(sizeof(Texto));
    novoTexto->conteudo = strdup(t);
    return novoTexto;
}
//2
void liberarTexto (Texto * t){
    if(t != NULL)
        free(t);
}
//3
unsigned int tamanhoTexto (Texto * t){
    unsigned int tamanho;
    
    if(t != NULL){
        tamanho = strlen(t->conteudo);
    }

    return tamanho;
}
//4
char * obterTexto (Texto * t){
    return t->conteudo;
}
//5
void mostrarTexto(Texto *t, unsigned int colunas) {
    int tamanhoT = strlen(t->conteudo);

    for (int i = 0; i < tamanhoT; i++) {
        printf("%c", t->conteudo[i]);

        if ((i + 1) % colunas == 0) {
            printf("\n");
        }
    }

        printf("\n");
    
}
//6
Texto * copiarTexto (Texto * t){
    return criarTexto(t->conteudo);
}
//7
void substituirTexto (Texto * t, char * alteracao){
    strcpy(t->conteudo, alteracao);
}
//8
Texto * concatenarTextos (Texto * t1, Texto * t2){
    int tamanho1 = tamanhoTexto(t1), tamanho2 = tamanhoTexto(t2);
    char *novo = (char *) malloc((tamanho1 + tamanho2));

    strcpy(novo, t1->conteudo);
    strcat(novo, t2->conteudo);

    Texto *novoTexto = criarTexto(novo);

    free(novo);
    return novoTexto;    

}
//9
char * obterSubtexto (Texto * t, unsigned int inicio, unsigned int tamanho){
    unsigned int i, j;

    if(inicio < 1 || inicio > strlen(t->conteudo)){
        return NULL;
    }

    if(tamanho > tamanhoTexto(t)){
        tamanho = tamanhoTexto(t);
    }

    char *subtexto = (char *) malloc(tamanho+1);

    for(i = (inicio - 1), j = 0; i < tamanho; i++, j++){
        subtexto[j] = t->conteudo[i];
    }
    subtexto[j] = '\0';
    
    return subtexto;
}
//10
unsigned int encontrarSubtexto(Texto *t, char *subtexto, unsigned int ocorrencia){
    char *pos = t->conteudo;
    unsigned int i;
    for (i = 1; i < ocorrencia; ++i){
        pos = strstr(pos + 1, subtexto);
        if (pos == NULL) {
            return FALHA;
        }
    }
    return (unsigned int)(pos - t->conteudo) + 1;
}
//11
int compararTextos (Texto * t1, Texto * t2){

    if(tamanhoTexto(t1) > tamanhoTexto(t2)){
        return MAIOR;
    }else if(tamanhoTexto(t1) < tamanhoTexto(t2)){
        return MENOR;
    }else if(tamanhoTexto(t1) == tamanhoTexto(t2)){
        return IGUAL;
    }

    return 0;
}


void opcoes(){
    printf("------------------------------------------------------\n");
    printf("BEM VINDOS AO TEXTO CONSTRUCTOR\n");
    printf("------------------------------------------------------\n");
    
    printf("1. Criar texto.\n");
    printf("2. Excluir um texto\n");
    printf("3. Tamanho do texto.\n");
    printf("4. Obter texto.\n");
    printf("5. Mostrar texto.\n");
    printf("11. Comparar textos.\n");
    printf("0 - Encerra o programa\n");
    printf("99 - Mostra as opcoes novamente\n");

    
}

int main(){
    opcoes();
    int opcao = -1;
    char textoAux[1000];
    Texto *texto = NULL;
    Texto *copia = NULL;


    while(1){
        printf("Selecione sua opcao: ");
        scanf("%d", &opcao);

        if(opcao == 0){
            printf("Encerrado!");
            liberarTexto(texto);
            liberarTexto(copia);
            break;
        }

        if(opcao == 1){
            printf("Digite o texto a ser criado(limite de 1000 caracteres):\n");
            scanf(" %[^\n]s", textoAux);

            texto = criarTexto(textoAux);
            printf("Texto criado com sucesso!\n\n");

        }else if(opcao == 2){
            if(texto != NULL){
                liberarTexto(texto);
                texto = NULL;
                printf("Texto excluído com sucesso\n\n");
            }else{
                printf("Texto inexistente.\n\n");
                continue;
            }
        
        }else if(opcao == 3){
            if(texto != NULL){
                printf("Tamanho do texto: %d\n\n", tamanhoTexto(texto));
            }else{
                printf("Texto inexistente.\n\n");
            }
        }else if(opcao == 4){
            if(texto != NULL){
                printf("Seu texto: %s\n\n", obterTexto(texto));
            }else{
                printf("Texto inexistente.\n\n");
            }
        }
        else if(opcao == 5){
            unsigned int colunasEscolhidas;

            if(texto != NULL){
                printf("Com quantas colunas deseja que o texto seja apresentado?\n");
                scanf("%u", &colunasEscolhidas);

                mostrarTexto(texto, colunasEscolhidas);   
            }else{
                printf("Texto inexistente.\n\n");
                continue;
            }
            
        }else if(opcao == 6){
            if(texto != NULL){
                copia = copiarTexto(texto);
                printf("Texto copiado: %s\n\n", obterTexto(copia));
            }else{
                printf("Texto inexistente.\n\n");
            }
            
        }else if(opcao == 7){

            if(texto != NULL){
                printf("\nTexto atual: %s\n", obterTexto(texto));
                printf("Escreva o texto que vai substituir:\n");
                scanf(" %[^\n]s", textoAux);
                substituirTexto(texto, textoAux);
                printf("\nTexto substituído com sucesso. Novo texto: %s\n\n", obterTexto(texto));
            }else{
                printf("Texto inexistente.\n\n");
            }
        }else if(opcao == 8){
            if(texto != NULL){
                printf("Texto existente: %s\n", obterTexto(texto));
                printf("Digite outro texto pra juntar a esse:\n");

                char textoConcat[1000];
                scanf(" %[^\n]s", textoConcat);

                Texto *texto2 = criarTexto(textoConcat);
                Texto *concatenado = concatenarTextos(texto, texto2);

                strcpy(texto->conteudo, concatenado->conteudo);

                printf("Textos concatenados:\n");
                mostrarTexto(concatenado, 70);
                liberarTexto(texto2);
                liberarTexto(concatenado);
            }else{
                printf("Texto inexistente.\n\n");
            }
        }else if(opcao == 9){
            unsigned int inicio, tamanho;

            printf("Qual a posição inicial?");
            scanf("%u", &inicio);

            printf("Qual o tamanho do subtexto?");
            scanf("%u", &tamanho);

            char *subtexto = obterSubtexto(texto, inicio, tamanho);
            printf("Subtexto: %s\n", subtexto);
            free(subtexto);
        }else if(opcao == 10){
            unsigned int escolha = 0;
            if (texto != NULL){
                    printf("Digite o subtexto: ");
                    scanf(" %[^\n]s", textoAux);
                    printf("Digite a ocorrencia: ");
                    scanf("%u", &escolha);
                    unsigned int posicao = encontrarSubtexto(texto, textoAux, escolha);
                    if (posicao != 0){
                        printf("Ocorrencia encontrada na posicao %u.\n", posicao);
                    } else {
                        printf("Ocorrência não encontrada.\n");
                    }
                } else {
                    printf("Texto inexistente.\n");
                }
        }else if(opcao == 11){
            if(texto != NULL){
                printf("Digite outro texto:");
                scanf(" %[^\n]s", textoAux);
                Texto *t2 = criarTexto(textoAux);

                int comparacao = compararTextos(texto, t2);


                if (comparacao < 0){
                    printf("Os textos sao diferentes, e o primeiro e menor.\n");
                } else if (comparacao > 0){
                    printf("Os textos sao diferentes, e o primeiro e maior.\n");
                } else {
                    printf("Os textos sao iguais em tamanho.\n");
                }
                
                liberarTexto(t2);
                } else {
                    printf("Texto inexistente. \n");
                }
             
        } else if(opcao == 99){
            opcoes();
        }
    }

    return 0;
}