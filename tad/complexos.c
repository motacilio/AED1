#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define TOTAL_NUMS 1000000 
#define SUCESSO 1
#define FALHA 0
#define TRUE 1
#define FALSE 0 
#define CRESCENTE 1
#define DECRESCENTE 0

// ARQUIVO.h
void opcoes();
typedef struct complexo Complexo;
typedef struct conjunto Conjunto;
Complexo criaComplexo(double real, double imaginario);
int criaConjunto(Conjunto *C);
int conjuntoVazio(Conjunto *C);
int insereElementoConjunto(Complexo x, Conjunto *C);
int excluirElementoConjunto(Complexo x, Conjunto *C);
int tamanhoConjunto(Conjunto *C);
int pertenceConjunto(Complexo x, Conjunto *C);
int conjuntosIdenticos(Conjunto *C1, Conjunto *C2);
int subconjunto(Conjunto *C1, Conjunto *C2);
Conjunto complemento(Conjunto *C1, Conjunto *C2);
Conjunto uniao(Conjunto *C1, Conjunto *C2);
Conjunto interseccao(Conjunto *C1, Conjunto *C2);
Conjunto diferenca(Conjunto *C1, Conjunto *C2);
int copiarConjunto(Conjunto *C1, Conjunto *C2);
int destroiConjunto(Conjunto *C);

/*
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
Conjunto (Conjunto *, Conjunto *);
Conjunto conjuntoPartes(Conjunto *);
void mostraConjunto(Conjunto *, int);
int copiarConjunto(Conjunto *, Conjunto *);
int destroiConjunto(Conjunto *);
*/
// ARQUIVO.c

void opcoes(){
    printf("------------------------------------------------------\n");
        printf("BEM-VINDO AO CONJUNTO CONSTRUCTOR\n");
        printf("------------------------------------------------------\n");
        printf("1 - Criar novo conjunto\n");
        printf("2 - Verificar se um conjunto esta vazio\n");
        printf("3 - Inserir elemento em um conjunto\n");
        printf("4 - Excluir elemento de um conjunto\n");
        printf("5 - Calcular a cardinalidade de um conjunto\n");
        printf("6 - verificar se o elemento x pertence a um conjunto\n");
        printf("7 - Verificar se dois conjuntos sao identicos\n");
        printf("8 - Identificar se o conjunto C1 é subconjunto de C2\n");
        printf("9 - Gerar o complemento do conjunto C1 em relacao ao conjunto C2\n");
        printf("10 - Gerar a uniao do conjunto C1 em relacao a C2\n");
        printf("11 - Gerar a interssecção do conjunto C1 em relacao a C2\n");
        printf("12 - Gerar a diferença entre o conjunto C1 em relacao a C2\n");
        printf("13 - mostrar os elementos de um conjunto\n");
        printf("14 - copiar o conjunto C1 para o conjunto C2\n");
        printf("15 - Destruir um conjunto \n");
        printf("0 - Parar o programa\n");
        printf("99 - Mostrar este menu novamente\n");
}

struct conjunto{
    int tamanho;
    Complexo *elementos;
};

struct complexo{
    double real;
    double imaginario;
};

Complexo criaComplexo(double real, double imaginario){
    Complexo C;
    C.imaginario = imaginario;
    C.real = real;
    return C;
}


void ordenaComplexo(Conjunto *C){
    int i, j;
    int n = C->tamanho;

    for(i = 0; i < n - 1; i++){
        for(j = 0; j < n - 1; j++){
            int comparacao;
            comparacao = (C->elementos[j].real > C->elementos[j + 1].real) || 
            ((C->elementos[j].real == C->elementos[j + 1].real) && 
            (C->elementos[j].imaginario > C->elementos[j + 1].imaginario));

            if(comparacao){
                Complexo aux = C->elementos[j];
                C->elementos[j] = C->elementos[j + 1];
                C->elementos[j + 1] = aux;
            }
        }
    }
}

int criaConjunto(Conjunto *C){
    if(C == NULL){
        return FALHA;
    } 
    C->elementos = (Complexo *) calloc(TOTAL_NUMS, sizeof(Complexo));
    C->tamanho = 0;
    return SUCESSO;
}

int conjuntoVazio(Conjunto *C){
    return C->tamanho == 0 ? TRUE : FALSE;
}

int insereElementoConjunto(Complexo x, Conjunto *C){
    if(C == NULL || C->elementos == NULL || C->tamanho >= TOTAL_NUMS){
        return FALHA;
    } else{
        for(int i = 0; i < C->tamanho; i++){
            if(C->elementos[i].real == x.real && C->elementos[i].imaginario == x.imaginario){
                printf("Elemento ja no conjunto!\n");
                return FALHA;
            }
        }
    }
    C->elementos[C->tamanho] = x;
    C->tamanho++;

    return SUCESSO;
}

int excluirElementoConjunto(Complexo x, Conjunto *C){
    if(C == NULL || C->elementos == NULL){
        return FALHA;
    }
    int indX; 
    for(int i = 0; i < C->tamanho; i++){
        if(C->elementos[i].real == x.real && C->elementos[i].imaginario == x.imaginario){
            indX = i;
            break;
        } else{
            printf("Elemento nao existente no conjunto\n");
            return FALHA;       
        }
    }
    for (int i = indX; i < C->tamanho - 1; i++) {
    C->elementos[i] = C->elementos[i + 1];
    }
    C->tamanho--;

    return SUCESSO;
}

int tamanhoConjunto(Conjunto *C){
    return C->tamanho;
}

int conjuntosIdenticos(Conjunto *C1, Conjunto *C2){
    if(C1 == NULL || C2 == NULL || (C1->tamanho != C2->tamanho)){
        return FALSE;
    }
    ordenaComplexo(C1);
    ordenaComplexo(C2);
    for(int i = 0; i < C1->tamanho; i++){
            if(C1->elementos[i].real != C2->elementos[i].real || C1->elementos[i].imaginario != C2->elementos[i].imaginario){
                return FALHA;
            }
        }
    return TRUE;
}


void mostraConjunto(Conjunto *C, int ordem){
    if(C != NULL){
        ordenaComplexo(C);
        int auxVir = 0;
        if(ordem == CRESCENTE){
            printf("{");

            for(int i = 0; i < C->tamanho; i++){
                if(C->elementos[i].imaginario >= 0 ){
                printf("%.2lf + %.2lfi", C->elementos[i].real, C->elementos[i].imaginario);
                } else{
                printf("%.2lf  %.2lfi", C->elementos[i].real, C->elementos[i].imaginario);
                }
                auxVir++;
                if(auxVir <  C->tamanho){
                    printf(", ");
                }
            }
            printf("}\n");
        } else if (ordem == DECRESCENTE){
            printf("{");
            for(int i = C->tamanho - 1; i >= 0; i--){
                if(C->elementos[i].imaginario >= 0 ){
                    printf("%.2lf + %.2lfi", C->elementos[i].real, C->elementos[i].imaginario);
                } else {
                    printf("%.2lf  %.2lfi", C->elementos[i].real, C->elementos[i].imaginario);
                }
                auxVir++;
                if(auxVir <  C->tamanho){
                    printf(", ");
                }

            }
            printf("}\n");
        } 
    }
}

int pertenceConjunto(Complexo x, Conjunto *C){
    for(int i = 0; i < C->tamanho; i++){
            if(C->elementos[i].real == x.real && C->elementos[i].imaginario == x.imaginario){
                return TRUE;
            }
    }
    return FALSE;
}

int subconjunto(Conjunto *C1, Conjunto *C2){

    if(C1 == NULL || C2 == NULL || C1->tamanho > C2->tamanho){
        return FALSE;
    }
    for(int i = 0; i < C1->tamanho; i++){
        if(!pertenceConjunto(C1->elementos[i], C2)){
            return FALSE;
        }
    }
    return TRUE;
}

Conjunto complemento(Conjunto *C1, Conjunto *C2){
    Conjunto *C3 = (Conjunto *)malloc(sizeof(Conjunto));
    criaConjunto(C3);

    int i;
    for (i = 0; i < C2->tamanho; i++)
    {
        int estaEmC1 = pertenceConjunto(C2->elementos[i], C1);

        if (estaEmC1 == 0)
        {
            insereElementoConjunto(C2->elementos[i], C3);
        }
    }

    if (C3->tamanho == C2->tamanho)
    {
        C3->elementos = NULL;
        C3->tamanho = 0;
        return *C3;
    }

    return *C3;
}

Conjunto uniao(Conjunto *C1, Conjunto *C2)
{
    Conjunto conjUniao;
    criaConjunto(&conjUniao);

    int i;
    for (i = 0; i < C1->tamanho; i++)
    {
        int elemC1 = pertenceConjunto(C1->elementos[i], &conjUniao);
        if (elemC1 == 0)
        {
            insereElementoConjunto(C1->elementos[i], &conjUniao);
        }
    }

    for (i = 0; i < C2->tamanho; i++)
    {
        int elemC2 = pertenceConjunto(C2->elementos[i], &conjUniao);
        if (elemC2 == 0)
        {
            insereElementoConjunto(C2->elementos[i], &conjUniao);
        }
    }

    if(conjUniao.tamanho > TOTAL_NUMS){
        printf("Tamanho estourou o limite\n");
        conjUniao.tamanho = 0;
        free(conjUniao.elementos);
        conjUniao.elementos = NULL;
    }    

    return conjUniao;
}

Conjunto interseccao(Conjunto *C1, Conjunto *C2)
{
    Conjunto conjInter;
    criaConjunto(&conjInter);

    int i;
    for (i = 0; i < C2->tamanho; i++)
    {
        int estaEmC1 = pertenceConjunto(C2->elementos[i], C1);

        if (estaEmC1 == 1)
        {
            insereElementoConjunto(C2->elementos[i], &conjInter);
        }
    }

    return conjInter;
}

Conjunto diferenca(Conjunto *C1, Conjunto *C2)
{
    Conjunto conjDiff;
    criaConjunto(&conjDiff);

    int i;
    for (i = 0; i < C1->tamanho; i++)
    {
        int estaEmC2 = pertenceConjunto(C1->elementos[i], C2);

        if (estaEmC2 == 0)
        {
            insereElementoConjunto(C1->elementos[i], &conjDiff);
        }
    }
    return conjDiff;
}

int copiarConjunto(Conjunto *C1, Conjunto *C2){
    if (C1 == NULL || C2 == NULL)
    {
        return 0;
    }

    for(int i = C2->tamanho, j = 0; j < C1->tamanho; j++, i++){
        insereElementoConjunto(C1->elementos[j], C2);
    }

    if(C2->tamanho > TOTAL_NUMS){
        printf("A copia estourou o tamanho maximo permitido\n");
        C2->tamanho = 0;
        free(C2->elementos);
        C2->elementos = NULL;
    }

    return 1;
}

int destroiConjunto(Conjunto *C){
     if (C == NULL) {
        return FALHA;
    }
    free(C->elementos);
    C->elementos = NULL; 
    C->tamanho = 0; 
    C = NULL;
    return 1; 
}


// ARQUIVO main

int main(){
    opcoes();
    Conjunto *conjuntos = NULL;
    int numConjuntos = 0;
    int conjunto1, conjunto2, opcao = -1;

    while(1){
        printf("\nDigite sua opcao: \n");
        scanf("%d", &opcao);

        if(opcao == 1){
            Conjunto *novoConjunto = (Conjunto *) realloc(conjuntos, (numConjuntos + 1) * sizeof(Conjunto));

            if(novoConjunto == NULL){
                printf("Erro ao alocar conjunto\n");
            } else {
                conjuntos = novoConjunto;
                if(criaConjunto(&conjuntos[numConjuntos]) == FALHA){
                    printf("Erro ao criar conjunto\n");
                } else{
                    numConjuntos++;
                    printf("Conjunto %d criado\n", numConjuntos);
                }
            }
        } else if(opcao == 2){
            printf("Digite o conjunto: \n");
            scanf("%d", &conjunto1); conjunto1--;

            int resultado = conjuntoVazio(&conjuntos[conjunto1]);
            if(resultado == TRUE){
                printf("O conjunto eh vazio\n");
            } else {
                printf("O conjunto nao eh vazio\n");
            }
        } else if(opcao == 3){
            printf("Digite o conjunto: \n");
            scanf("%d", &conjunto1); conjunto1--;

            printf("Digite a parte real: \n"); 
            double real; scanf("%lf", &real);
            printf("Digite a parte imaginaria: \n");
            double imaginaria; scanf("%lf", &imaginaria);

            Complexo c = criaComplexo(real, imaginaria);

            int resultado = insereElementoConjunto(c, &conjuntos[conjunto1]);
            if(resultado == SUCESSO){
                printf("Elemento inserido com sucesso\n");
            } else{
                printf("Falha ao inserir elemento\n");
            }
        } else if(opcao == 4){
            printf("Digite o conjunto: \n");
            scanf("%d", &conjunto1); conjunto1--;

            printf("Digite a parte real: \n"); 
            double real; scanf("%lf", &real);
            printf("Digite a parte imaginaria: \n");
            double imaginaria; scanf("%lf", &imaginaria);

            Complexo c = criaComplexo(real, imaginaria);

            int resultado = excluirElementoConjunto(c, &conjuntos[conjunto1]);
            if(resultado == SUCESSO){
                printf("Elemento excluido com sucesso\n");
            } else{
                printf("Falha ao excluir elemento\n");
            }
        } else if(opcao == 5){
            printf("Digite o conjunto: \n");
            scanf("%d", &conjunto1); conjunto1--;
            int aux = conjunto1++; 

            printf("O tamanho do conjunto %d eh: %d", aux, tamanhoConjunto(&conjuntos[conjunto1]));
        } else if(opcao == 6){
            printf("Digite o conjunto: \n");
            scanf("%d", &conjunto1); conjunto1--;

            printf("Digite a parte real: \n"); 
            double real; scanf("%lf", &real);
            printf("Digite a parte imaginaria: \n");
            double imaginaria; scanf("%lf", &imaginaria);

            Complexo c = criaComplexo(real, imaginaria);

            int resultado = pertenceConjunto(c, &conjuntos[conjunto1]);
            if(resultado == TRUE){
                printf("Elemento pertence ao conjunto\n");
            } else{
                printf("Elemento nao pertence ao conjunto\n");
            }

        } else if(opcao == 7){
            printf("Digite o primeiro conjunto: \n");
            scanf("%d", &conjunto1); conjunto1--;
            printf("Digite o segundo conjunto: \n");
            scanf("%d", &conjunto2); conjunto2--;

            int resultado = conjuntosIdenticos(&conjuntos[conjunto1], &conjuntos[conjunto2]);

            if(resultado == TRUE){
                printf("Os conjuntos sao identicos\n");
            } else{
                printf("Os conjuntos nao sao identicos\n");
            }

        } else if(opcao == 8){
            printf("Digite o primeiro conjunto: \n");
            scanf("%d", &conjunto1); conjunto1--;
            printf("Digite o segundo conjunto: \n");
            scanf("%d", &conjunto2); conjunto2--;
            
            int resultado = subconjunto(&conjuntos[conjunto1], &conjuntos[conjunto2]);
            if(resultado == TRUE){
                printf("O primeiro conjunto eh subconjunto do segundo\n");
            } else{
                printf("O primeiro conjnuto nao eh subconjunto do segundo\n");
            }
        } else if(opcao == 9){
            printf("Digite o primeiro conjunto: \n");
            scanf("%d", &conjunto1); conjunto1--;
            printf("Digite o segundo conjunto: \n");
            scanf("%d", &conjunto2); conjunto2--;

            Conjunto novoComplemento = complemento(&conjuntos[conjunto1], &conjuntos[conjunto2]);
            conjuntos = (Conjunto *)realloc(conjuntos, (numConjuntos + 1) * sizeof(Conjunto));
            if (conjuntos == NULL)
            {
                printf("Falha ao alocar memoria\n");
                return 1;
            }
            conjuntos[numConjuntos] = novoComplemento;
            numConjuntos++;
            printf("Conjunto %d criado!\n", numConjuntos);
        } else if(opcao == 10){
            
            printf("Digite o primeiro conjunto desejado: \n");
            scanf("%d", &conjunto1);
            conjunto1--;
            printf("Digite o segundo conjunto desejado: \n");
            scanf("%d", &conjunto2);
            conjunto2--;

            Conjunto novaUniao = uniao(&conjuntos[conjunto1], &conjuntos[conjunto2]);
            conjuntos = (Conjunto *)realloc(conjuntos, (numConjuntos + 1) * sizeof(Conjunto));
            if (conjuntos == NULL)
            {
                printf("Falha ao alocar memoria\n");
                return 1;
            }
            conjuntos[numConjuntos] = novaUniao;
            numConjuntos++;
            printf("Conjunto %d criado!\n", numConjuntos);

        } else if(opcao == 11){
            printf("Digite o primeiro conjunto desejado: \n");
            scanf("%d", &conjunto1);
            conjunto1--;
            printf("Digite o segundo conjunto desejado: \n");
            scanf("%d", &conjunto2);
            conjunto2--;

            Conjunto novaInter = interseccao(&conjuntos[conjunto1], &conjuntos[conjunto2]);
            conjuntos = (Conjunto *)realloc(conjuntos, (numConjuntos + 1) * sizeof(Conjunto));
            if (conjuntos == NULL)
            {
                printf("Falha ao alocar memoria\n");
                return 1;
            }
            conjuntos[numConjuntos] = novaInter;
            numConjuntos++;
            printf("Conjunto %d criado!\n", numConjuntos);
        }  else if (opcao == 12)
        {
            printf("Digite o primeiro conjunto desejado: \n");
            scanf("%d", &conjunto1);
            conjunto1--;
            printf("Digite o segundo conjunto desejado: \n");
            scanf("%d", &conjunto2);
            conjunto2--;

            Conjunto novaDiff = diferenca(&conjuntos[conjunto1], &conjuntos[conjunto2]);
            conjuntos = (Conjunto *)realloc(conjuntos, (numConjuntos + 1) * sizeof(Conjunto));
            if (conjuntos == NULL)
            {
                printf("Falha ao alocar memoria\n");
                return 1;
            }
            conjuntos[numConjuntos] = novaDiff;
            numConjuntos++;
            printf("Conjunto %d criado!\n", numConjuntos);
        }
        else if(opcao == 13){
            printf("Digite o conjunto: \n");
            scanf("%d", &conjunto1); conjunto1--;
            printf("Digite a ordem: [1]Crescente ou [2]Decrescente\n");
            int ordem; scanf("%d", &ordem);

            if(ordem == 1){
                mostraConjunto(&conjuntos[conjunto1], ordem);
            } else{
                mostraConjunto(&conjuntos[conjunto1], ordem);
            }
        } else if(opcao == 14){
            printf("Digite o primeiro conjunto: \n");
            scanf("%d", &conjunto1);
            conjunto1--;
            printf("Digite o segundo conjunto: \n");
            scanf("%d", &conjunto2);
            conjunto2--;

            int resultadoCopia = copiarConjunto(&conjuntos[conjunto1], &conjuntos[conjunto2]);

            if(resultadoCopia == 1){
                printf("Copia realizada com sucesso\n");
            } else {
                printf("Falha ao copiar \n");
            }
        } else if(opcao == 15){
            printf("Digite o conjunto a ser destruído: \n");
            scanf("%d", &conjunto1);
            conjunto1--;

            int resultadoDestruir = destroiConjunto(&conjuntos[conjunto1]);
            if(resultadoDestruir == 1){
                printf("Conjunto %d destruído!\n", ++conjunto1);
            } else {
                printf("falha ao destruir o conjunto\n");
            }
        }
        else if(opcao == 99){
            opcoes();
        } else if(opcao == 0){
             for(int i = 0; i < numConjuntos; i++){
                free(conjuntos[i].elementos);
            }
            free(conjuntos);
            break;
        }
    }



}