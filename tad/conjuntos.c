#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_ELEMENTOS 1000000 


/*-----------------------------------------------------------------
ARQUIVO.h
------------------------------------------------------------------*/
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

/*
---------------------------------------------------------------------------
ARQUIVO.c
--------------------------------------------------------------------------*/ 
void quicksort(int *arr, int baixo, int alto)
{
    if (baixo < alto)
    {
        int pivo = arr[alto];
        int i = baixo - 1;

        for (int j = baixo; j <= alto - 1; j++)
        {
            if (arr[j] < pivo)
            {
                i++;
                // Troca de elementos
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        // Troca do pivo
        int temp = arr[i + 1];
        arr[i + 1] = arr[alto];
        arr[alto] = temp;

        int indice_pivo = i + 1;

        // Chamadas recursivas
        quicksort(arr, baixo, indice_pivo - 1);
        quicksort(arr, indice_pivo + 1, alto);
    }
}

int buscaBin(int *vetor, int elemBuscado, int limInf, int limSup)
{
    int termoMedio;

    while (limInf <= limSup)
    {
        termoMedio = limInf + (limSup - limInf) / 2;

        if (vetor[termoMedio] == elemBuscado)
        {
            return termoMedio;
        }
        else if (elemBuscado < vetor[termoMedio])
        {
            limSup = termoMedio - 1;
        }
        else
        {
            limInf = termoMedio + 1;
        }
    }

    return -1; // Elemento não encontrado
}

struct conjunto
{
    int *elementos;
    int tamanho;
};

int criaConjunto(Conjunto *C)
{
    if (C == NULL)
    {
        return 0;
    }
    C->tamanho = 0;
    C->elementos = NULL;
    return 1;
}

int conjuntoVazio(Conjunto *C)
{
    if (C->tamanho == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int insereElementoConjunto(int x, Conjunto *C)
{
    if(C != NULL && C->tamanho < MAX_ELEMENTOS && x < LONG_MAX && x > LONG_MIN){
            
        quicksort(C->elementos, 0, C->tamanho - 1);
        int indElemento = buscaBin(C->elementos, x, 0, C->tamanho - 1);
        if (indElemento != -1)
        {
            printf("Elemento já presente no conjunto\n");
            return 0;
        }

        if (C->elementos == NULL)
        {
            C->elementos = (int *)malloc(sizeof(int));
            if (C->elementos == NULL)
            {
                return 0;
            }
            C->tamanho = 1;
            C->elementos[0] = x;
            return 1;
        }

        int *novoElementos = (int *)realloc(C->elementos, (C->tamanho + 1) * sizeof(int));
        if (novoElementos == NULL)
        {
            return 0;
        }
        C->elementos = novoElementos;
        C->elementos[C->tamanho] = x;
        C->tamanho++;

        return 1;
    }

    return 0;
}

int excluirElementoConjunto(int x, Conjunto *C)
{
    quicksort(C->elementos, 0, C->tamanho - 1);
    int indElemento = buscaBin(C->elementos, x, 0, C->tamanho - 1);
    if (indElemento == -1)
    {
        printf("Elemento não presente no conjunto\n");
        return 0;
    }
    else
    {
        for (int i = indElemento; i < C->tamanho - 1; i++)
        {
            C->elementos[i] = C->elementos[i + 1];
        }
        C->elementos = (int *)realloc(C->elementos, (C->tamanho - 1) * sizeof(int));
        C->tamanho--;  
        return 1;
    }
    return 0;
}

int tamanhoConjunto(Conjunto *C)
{
    return C->tamanho;
}

int maior(int x, Conjunto *C)
{
    quicksort(C->elementos, 0, C->tamanho - 1);
    int indElemen = buscaBin(C->elementos, x, 0, C->tamanho - 1);

    if (indElemen == -1)
    {
        return C->tamanho;
    }
    else
    {
        return C->tamanho - indElemen - 1;
    }
}


int menor(int x, Conjunto *C)
{
    quicksort(C->elementos, 0, C->tamanho - 1);
    int indElemen = buscaBin(C->elementos, x, 0, C->tamanho - 1);

    if (indElemen == -1)
    {
        // Elemento não encontrado, todos são menores
        return C->tamanho;
    }
    else
    {
        // Elemento encontrado, retorna a quantidade de elementos menores
        return indElemen;
    }
}


int pertenceConjunto(int x, Conjunto *C)
{
    int indElemen = buscaBin(C->elementos, x, 0, C->tamanho - 1);

    if (indElemen == -1)
    {
        return 0;
    }

    return 1;
}

int conjuntosIdenticos(Conjunto *C1, Conjunto *C2)
{
    int i;
    if (C1->tamanho != C2->tamanho)
    {
        return 0;
    }

    for (i = 0; i < C1->tamanho - 1; i++)
    {
        if (C1->elementos[i] != C2->elementos[i])
        {
            return 0;
        }
    }
    return 1;
}

int subconjunto(Conjunto *C1, Conjunto *C2)
{
    if (C1->tamanho > C2->tamanho)
    {
        return 0;
    }

    int i;
    for (i = 0; i < C1->tamanho - 1; i++)
    {
        int elementoAt = C1->elementos[i];
        int pertenceC2 = pertenceConjunto(elementoAt, C2);

        if (pertenceC2 == 0)
        {
            return 0;
        }
    }
    return 1;
}

Conjunto complemento(Conjunto *C1, Conjunto *C2)
{
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

    if(conjUniao.tamanho > MAX_ELEMENTOS){
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

Conjunto conjuntoPartes(Conjunto *C)
{
    Conjunto conjuntoPartes;
    criaConjunto(&conjuntoPartes);

    int totalSubconjuntos = 1 << C->tamanho; // 2 elevado à potência do tamanho de C
    int i, j;

    for (i = 0; i < totalSubconjuntos; i++)
    {
        criaConjunto(&conjuntoPartes);
        for (j = 0; j < C->tamanho; j++)
        {
            if ((i & (1 << j)) != 0)
            {
                // Se o j-ésimo bit de i está definido, adiciona o elemento correspondente
                insereElementoConjunto(C->elementos[j], &conjuntoPartes);
            }
        }

        printf("Subconjunto %d: ", i + 1);
        mostraConjunto(&conjuntoPartes, 1);  

    }

    return conjuntoPartes;
}

void mostraConjunto(Conjunto *C, int ordem)
{
   
    if (ordem == 1)
    {   
        printf("{");
        for (int i = 0; i < C->tamanho; i++)
        {   
            printf("%d ", C->elementos[i]);
        }
        printf("}");
        printf("\n");
    }
    else if (ordem == 0)
    {   
        printf("{");
        for (int i = C->tamanho - 1; i >= 0; i--)
        {
            printf("%d ", C->elementos[i]);
        }
        printf("}");
        printf("\n");
    }
    else
    {
        printf("Ordem inválida! Digite 1 para crescente ou 0 para decrescente.\n");
    }
}

int copiarConjunto(Conjunto *C1, Conjunto *C2){
    if (C1 == NULL || C2 == NULL)
    {
        return 0;
    }

    for(int i = C2->tamanho, j = 0; j < C1->tamanho; j++, i++){
        insereElementoConjunto(C1->elementos[j], C2);
    }

    if(C2->tamanho > MAX_ELEMENTOS){
        printf("A copia estourou o tamanho maximo permitido\n");
        C2->tamanho = 0;
        free(C2->elementos);
        C2->elementos = NULL;
    }

    return 1;
}



int destroiConjunto(Conjunto *C) {
    if (C == NULL) {
        return 0;
    }
    free(C->elementos);
    C->elementos = NULL; 
    C->tamanho = 0; 

    return 1; 
}

int main()
{
        printf("------------------------------------------------------\n");
        printf("BEM-VINDO AO CONJUNTO CONSTRUCTOR\n");
        printf("------------------------------------------------------\n");
        printf("1 - Criar novo conjunto\n");
        printf("2 - Verificar se um conjunto esta vazio\n");
        printf("3 - Inserir elemento em um conjunto\n");
        printf("4 - Excluir elemento de um conjunto\n");
        printf("5 - Calcular a cardinalidade de um conjunto\n");
        printf("6 - Determinar quantos elementos de um conjunto sao maiores que x\n");
        printf("7 - Determinar quantos elementos de um conjunto sao menores que x\n");
        printf("8 - verificar se o elemento x pertence a um conjunto\n");
        printf("9 - Verificar se dois conjuntos sao identicos\n");
        printf("10 - Identificar se o conjunto C1 é subconjunto de C2\n");
        printf("11 - Gerar o complemento do conjunto C1 em relacao ao conjunto C2\n");
        printf("12 - Gerar a uniao do conjunto C1 em relacao a C2\n");
        printf("13 - Gerar a interssecção do conjunto C1 em relacao a C2\n");
        printf("14 - Gerar a diferença entre o conjunto C1 em relacao a C2\n");
        printf("15 - Gerar os subconjuntos de um conjunto\n");
        printf("16 - mostrar os elementos de um conjunto\n");
        printf("17 - copiar o conjunto C1 para o conjunto C2\n");
        printf("18 - Destruir um conjunto \n");
        printf("0 - Parar o programa\n");
        printf("99 - Mostrar este menu novamente");

    Conjunto *lisConjuntos = NULL;
    int qntConjuntos = 0; // o indice
    int conjun, conjun2;


    while (1)
    {

        printf("\n Digite a opcao desejada: \n");
        int opcao;
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            lisConjuntos = (Conjunto *)realloc(lisConjuntos, (qntConjuntos + 1) * sizeof(Conjunto));
            if (lisConjuntos == NULL)
            {
                printf("Falha ao criar conjunto\n");
                return 1;
            }
            criaConjunto(&lisConjuntos[qntConjuntos]);
            qntConjuntos++;
            printf("Conjunto %d criado!\n", qntConjuntos);
        }
        else if (opcao == 2)
        {
            printf("Digite o conjunto:\n");
            scanf("%d", &conjun);
            conjun--;
            

            int isVazio = conjuntoVazio(&lisConjuntos[conjun]);
            if(isVazio == 1){
                printf("Conjunto Vazio!\n");
            } else{
                printf("Conjunto nao vazio!");
            }
        }
        else if (opcao == 3)
        {

            printf("Digite o conjunto desejado:\n");
            scanf("%d", &conjun);
            printf("Digite o elemento a ser inserido:\n");
            int x;
            scanf("%d", &x);
            conjun--;

            quicksort(lisConjuntos[conjun].elementos, 0, (lisConjuntos[conjun].tamanho - 1));
            int elemento = buscaBin(lisConjuntos[conjun].elementos, x, 0, lisConjuntos[conjun].tamanho - 1);
            if (elemento == -1)
            {
                insereElementoConjunto(x, &lisConjuntos[conjun]);
            }
            else
            {
                printf("Elemento já no conjunto.\n");
            }
        }
        else if (opcao == 4)
        {
            printf("Digite o conjunto desejado:\n");
            scanf("%d", &conjun);
            conjun--;
            printf("Digite o elemento a ser excluido:\n");
            int x;
            scanf("%d", &x);

            excluirElementoConjunto(x, &lisConjuntos[conjun]);
        }
        else if (opcao == 5)
        {
            printf("Digite o conjunto desejado: \n");
            scanf("%d", &conjun);
            conjun--;
            int tamanho = tamanhoConjunto(&lisConjuntos[conjun]);
            if (tamanho == 0)
            {
                printf("Conjunto vazio!\n");
            }
            else
            {
                printf("%d", tamanho);
            }
        }
        else if (opcao == 6)
        {
            printf("Digite o conjunto desejado:\n");
            scanf("%d", &conjun);
            conjun = conjun - 1;
            printf("Digite o elemento:\n");
            int x;
            scanf("%d", &x);
            printf("%d", maior(x, &lisConjuntos[conjun]));
        }
        else if (opcao == 7)
        {
            printf("Digite o conjunto desejado:\n");
            scanf("%d", &conjun);
            conjun = conjun - 1;
            printf("Digite o elemento:\n");
            int x;
            scanf("%d", &x);
            printf("%d\n", menor(x, &lisConjuntos[conjun]));
        }
        else if (opcao == 8)
        {
            printf("Digite o conjunto desejado:\n");
            scanf("%d", &conjun);
            conjun = conjun - 1;
            printf("Digite o elemento:\n");
            int x;
            scanf("%d", &x);
            int pertence = pertenceConjunto(x, &lisConjuntos[conjun]);
            if(pertence == 1){
                printf("O elemento %d pertence ao conjunto!\n", x);
            } else{
                printf("O elemento %d nao pertence ao conjunto.\n", x);       
            }
            
        }
        else if (opcao == 9)
        {
            printf("Digite o primeiro conjunto desejado: \n");
            scanf("%d", &conjun);
            conjun--;
            printf("Digite o segundo conjunto desejado: \n");
            scanf("%d", &conjun2);
            conjun2--;
            int saoIdenticos = conjuntosIdenticos(&lisConjuntos[conjun], &lisConjuntos[conjun2]);
            if(saoIdenticos == 1){
                printf("Os conjuntos sao identicos\n");
            } else{
                printf("Os conjuntos nao sao identicos\n");
            }
        }
        else if (opcao == 10)
        {
            printf("Digite o primeiro conjunto desejado: \n");
            scanf("%d", &conjun);
            conjun--;
            printf("Digite o segundo conjunto desejado: \n");
            scanf("%d", &conjun2);
            conjun2--;
            int ehSubconjunto = subconjunto(&lisConjuntos[conjun], &lisConjuntos[conjun2]); 
            if(ehSubconjunto == 1){
                printf("O conjunto %d é subconjunto do conjunto %d", ++conjun, ++conjun2);
            } else{
                printf("O conjunto %d nao é subconjunto do conjunto %d", ++conjun, ++conjun2);       
            }
        }
        else if (opcao == 11)
        {
            printf("Digite o primeiro conjunto desejado: \n");
            scanf("%d", &conjun);
            conjun--;
            printf("Digite o segundo conjunto desejado: \n");
            scanf("%d", &conjun2);
            conjun2--;

            Conjunto novoComplemento = complemento(&lisConjuntos[conjun], &lisConjuntos[conjun2]);
            lisConjuntos = (Conjunto *)realloc(lisConjuntos, (qntConjuntos + 1) * sizeof(Conjunto));
            if (lisConjuntos == NULL)
            {
                printf("Falha ao alocar memoria\n");
                return 1;
            }
            lisConjuntos[qntConjuntos] = novoComplemento;
            qntConjuntos++;
            printf("Conjunto %d criado!\n", qntConjuntos);
        }
        else if (opcao == 12)
        {
            printf("Digite o primeiro conjunto desejado: \n");
            scanf("%d", &conjun);
            conjun--;
            printf("Digite o segundo conjunto desejado: \n");
            scanf("%d", &conjun2);
            conjun2--;

            Conjunto novaUniao = uniao(&lisConjuntos[conjun], &lisConjuntos[conjun2]);
            lisConjuntos = (Conjunto *)realloc(lisConjuntos, (qntConjuntos + 1) * sizeof(Conjunto));
            if (lisConjuntos == NULL)
            {
                printf("Falha ao alocar memoria\n");
                return 1;
            }
            lisConjuntos[qntConjuntos] = novaUniao;
            qntConjuntos++;
            printf("Conjunto %d criado!\n", qntConjuntos);
        }
        else if (opcao == 13)
        {
            printf("Digite o primeiro conjunto desejado: \n");
            scanf("%d", &conjun);
            conjun--;
            printf("Digite o segundo conjunto desejado: \n");
            scanf("%d", &conjun2);
            conjun2--;

            Conjunto novaInter = interseccao(&lisConjuntos[conjun], &lisConjuntos[conjun2]);
            lisConjuntos = (Conjunto *)realloc(lisConjuntos, (qntConjuntos + 1) * sizeof(Conjunto));
            if (lisConjuntos == NULL)
            {
                printf("Falha ao alocar memoria\n");
                return 1;
            }
            lisConjuntos[qntConjuntos] = novaInter;
            qntConjuntos++;
            printf("Conjunto %d criado!\n", qntConjuntos);
        }
        else if (opcao == 14)
        {
            printf("Digite o primeiro conjunto desejado: \n");
            scanf("%d", &conjun);
            conjun--;
            printf("Digite o segundo conjunto desejado: \n");
            scanf("%d", &conjun2);
            conjun2--;

            Conjunto novaDiff = diferenca(&lisConjuntos[conjun], &lisConjuntos[conjun2]);
            lisConjuntos = (Conjunto *)realloc(lisConjuntos, (qntConjuntos + 1) * sizeof(Conjunto));
            if (lisConjuntos == NULL)
            {
                printf("Falha ao alocar memoria\n");
                return 1;
            }
            lisConjuntos[qntConjuntos] = novaDiff;
            qntConjuntos++;
            printf("Conjunto %d criado!\n", qntConjuntos);
        }
        else if (opcao == 15)
        {
            printf("Digite o conjunto desejado: \n");
            scanf("%d", &conjun);
            conjun--;
            conjuntoPartes(&lisConjuntos[conjun]);
        }
        else if (opcao == 16)
        {
            printf("Digite o conjunto desejado: \n");
            scanf("%d", &conjun);
            conjun--;
            printf("Digite a ordem desejada: (1 - crescente | 0 - decrescente):\n");
            int ordem;
            scanf("%d", &ordem);
            printf("elementos: \n");
            mostraConjunto(&lisConjuntos[conjun], ordem);
        } else if(opcao == 17){

            printf("Digite o primeiro conjunto: \n");
            scanf("%d", &conjun);
            conjun--;
            printf("Digite o segundo conjunto: \n");
            scanf("%d", &conjun2);
            conjun2--;

            int resultadoCopia = copiarConjunto(&lisConjuntos[conjun], &lisConjuntos[conjun2]);

            if(resultadoCopia == 1){
                printf("Copia realizada com sucesso\n");
            } else {
                printf("Falha ao copiar \n");
            }
        } else if(opcao == 18){
            printf("Digite o conjunto a ser destruído: \n");
            scanf("%d", &conjun);
            conjun--;

            int resultadoDestruir = destroiConjunto(&lisConjuntos[conjun]);
            if(resultadoDestruir == 1){
                printf("Conjunto %d destruído!\n", ++conjun);
            } else {
                printf("falha ao destruir o conjunto\n");
            }
        } else if(opcao == 99){
            printf("------------------------------------------------------\n");
            printf("BEM-VINDO AO CONJUNTO CONSTRUCTOR\n");
            printf("------------------------------------------------------\n");
            printf("1 - Criar novo conjunto\n");
            printf("2 - Verificar se um conjunto esta vazio\n");
            printf("3 - Inserir elemento em um conjunto\n");
            printf("4 - Excluir elemento de um conjunto\n");
            printf("5 - Calcular a cardinalidade de um conjunto\n");
            printf("6 - Determinar quantos elementos de um conjunto sao maiores que x\n");
            printf("7 - Determinar quantos elementos de um conjunto sao menores que x\n");
            printf("8 - verificar se o elemento x pertence a um conjunto\n");
            printf("9 - Verificar se dois conjuntos sao identicos\n");
            printf("10 - Identificar se o conjunto C1 é subconjunto de C2\n");
            printf("11 - Gerar o complemento do conjunto C1 em relacao ao conjunto C2\n");
            printf("12 - Gerar a uniao do conjunto C1 em relacao a C2\n");
            printf("13 - Gerar a interssecção do conjunto C1 em relacao a C2\n");
            printf("14 - Gerar a diferença entre o conjunto C1 em relacao a C2\n");
            printf("15 - Gerar os subconjuntos de um conjunto\n");
            printf("16 - mostrar os elementos de um conjunto\n");
            printf("17 - copiar o conjunto C1 para o conjunto C2\n");
            printf("18 - Destruir um conjunto \n");
            printf("0 - Parar o programa\n");
            printf("99 - Mostrar este menu novamente");
        }
        else if (opcao == 0)
        {
            for(int i = 0; i < qntConjuntos; i++){
                free(lisConjuntos[i].elementos);
            }
            break;
        }
    }
}
