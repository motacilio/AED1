#include <stdio.h>
#include <stdlib.h>

void Binario(int num);

int main()
{

    int qntd;
    scanf("%d", &qntd);

    int *numsDec = (int *) calloc(qntd, sizeof(int));

    int i;
    for (i = 0; i < qntd; i++)
    {
        int num;
        scanf("%d", &num);
        numsDec[i] = num;
    }

    for(i = 0; i < qntd; i++){
        Binario(numsDec[i]);
        printf("\n");
    }
}

void Binario(int num)
{
    if (num > 0)
    {
        Binario(num / 2);
        printf("%d", num % 2);
    }
}