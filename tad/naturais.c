#include <stdio.h>
#include <stdlib.h>
#include "naturais.h"
#include <limits.h>

void exibirArray(int *elementos, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d ", elementos[i]);
    }
    printf("\n");
}

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
    quicksort(C->elementos, 0, C->tamanho - 1);
    return 1;
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
        C->elementos = realloc(C->elementos, (C->tamanho - 1) * sizeof(int));
        C->tamanho--;
        quicksort(C->elementos, 0, C->tamanho - 1);
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
    int i, qntMaiores = 0;
    if (indElemen == 0)
    {
        return 0;
    }
    else if (indElemen != -1)
    {
        return C->tamanho - indElemen - 1;
    }
    else if (indElemen == -1)
    {
        for (i = 0; i < C->tamanho - 1; i++)
        {
            int elementoAtual = C->elementos[i];
            if (elementoAtual > x)
            {
                qntMaiores++;
            }
        }
        return qntMaiores;
    }
    return -1;
}

int menor(int x, Conjunto *C)
{
    int i, qntMenores = 0;
    for (i = 0; i < C->tamanho - 1; i++)
    {
        int elementoAtual = C->elementos[i];
        if (elementoAtual < x)
        {
            qntMenores++;
        }
    }

    if (qntMenores == C->tamanho - 1)
    {
        return 0;
    }
    return qntMenores;
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

    quicksort(conjUniao.elementos, 0, conjUniao.tamanho - 1);

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

Conjunto diferenca(Conjunto *C1, Conjunto *C2){
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

Conjunto conjuntoPartes(Conjunto *C){
    Conjunto *conjPartes = NULL;
    int qntConjPartes = 0;
    int i, j;
    for(i = 0; i<C->tamanho - 1; i++){
        Conjunto subConjAtual;
        criaConjunto(&subConjAtual);
        for(j = i; j<C->tamanho - 1; j++){
            insereElementoConjunto(C->elementos[j], &subConjAtual);
        }
        conjPartes = (Conjunto *)realloc(conjPartes, (qntConjPartes + 1) * sizeof(Conjunto));
        conjPartes->elementos[qntConjPartes] = &subConjAtual;
        qntConjPartes++;
    }
    return *conjPartes;
}

int main()
{

    Conjunto *lisConjuntos = NULL;
    int qntConjuntos = 0; // o indice
    int conjun, conjun2;

    while (1)
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
        printf("99 - mostrar os elementos de um conjunto\n");
        printf("Digite a opcao desejada: \n");
        int opcao;
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            lisConjuntos = (Conjunto *)realloc(lisConjuntos, (qntConjuntos + 1) * sizeof(Conjunto));
            if (lisConjuntos == NULL)
            {
                printf("Falha ao alocar memoria\n");
                return 1;
            }
            criaConjunto(&lisConjuntos[qntConjuntos]);
            qntConjuntos++;
            printf("Conjunto %d criado!\n", qntConjuntos);
        }
        else if (opcao == 2)
        {
            printf("Digite o conjunto desejado:\n");
            scanf("%d", &conjun);
            int isVazio = conjuntoVazio(&lisConjuntos[conjun - 1]);
            printf("%d\n\n", isVazio);
        }
        else if (opcao == 3)
        {

            printf("Digite o conjunto desejado:\n");
            scanf("%d", &conjun);
            printf("Digite o elemento a ser inserido:\n");
            int x;
            scanf("%d", &x);

            quicksort(lisConjuntos[conjun - 1].elementos, 0, (lisConjuntos[conjun - 1].tamanho - 1));
            int elemento = buscaBin(lisConjuntos[conjun - 1].elementos, x, 0, lisConjuntos[conjun - 1].tamanho - 1);
            if (elemento == -1)
            {
                insereElementoConjunto(x, &lisConjuntos[conjun - 1]);
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
            conjun = conjun - 1;
            printf("Digite o elemento a ser excluido:\n");
            int x;
            scanf("%d", &x);

            excluirElementoConjunto(x, &lisConjuntos[conjun]);
            exibirArray(lisConjuntos[conjun].elementos, lisConjuntos[conjun].tamanho);
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

            printf("%d\n", pertenceConjunto(x, &lisConjuntos[conjun]));
        }
        else if (opcao == 9)
        {
            printf("Digite o primeiro conjunto desejado: \n");
            scanf("%d", &conjun);
            conjun--;
            printf("Digite o segundo conjunto desejado: \n");
            scanf("%d", &conjun2);
            conjun2--;
            printf("%d\n", conjuntosIdenticos(&lisConjuntos[conjun], &lisConjuntos[conjun2]));
        }
        else if (opcao == 10)
        {
            printf("Digite o primeiro conjunto desejado: \n");
            scanf("%d", &conjun);
            conjun--;
            printf("Digite o segundo conjunto desejado: \n");
            scanf("%d", &conjun2);
            conjun2--;
            printf("%d \n", subconjunto(&lisConjuntos[conjun], &lisConjuntos[conjun2]));
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
        } else if(opcao == 13){
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

        } else if(opcao == 14){
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
        else if (opcao == 0)
        {
            break;
        }
        else if (opcao == 99)
        {
            printf("Digite o conjunto desejado: \n");
            scanf("%d", &conjun);
            conjun--;
            exibirArray(lisConjuntos[conjun].elementos, lisConjuntos[conjun].tamanho);
        }
    }
}
