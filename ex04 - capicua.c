#include <stdio.h>

int main(){

    int qntdNums, num, numAux, numInv = 0;

    printf("Digite a quantidade de Numeros: "); scanf("%d", &qntdNums);

    for(int i = 1; i <= qntdNums; i++){

        printf("Digite o numero: "); scanf("%d", &num);
        numAux = num;

        while(numAux >= 1){
            numInv = (numInv * 10) + (numAux % 10);
            numAux /= 10;    
        }

        if(numInv == num){
            printf("yes\n");
        } else{
            printf("no\n");
        }

        printf("%d %d", num, numInv);


    }
    
    



}