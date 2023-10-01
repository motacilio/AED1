#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    int qntdNums, num, numAux, numInv = 0;

    // printf("Digite a quantidade de Numeros: "); 
    // laço para verificar se a qntd numeros é maior que 0
    while(1){
        scanf("%d", &qntdNums);
        if(qntdNums >= 0){
            break;
        } 
    }

    char **res = (char **) malloc(qntdNums * sizeof(char *));

    for(int i = 0; i < qntdNums; i++){
        res[i] = (char *) malloc(4 * sizeof(char));
    }

    for(int i = 0; i < qntdNums; i++){

        //printf("Digite o numero: "); 
        scanf("%d", &num);
        numAux = num;
        numInv = 0;

        while(numAux >= 1){
            numInv = (numInv * 10) + (numAux % 10);
            numAux /= 10;    
        }

        if(numInv == num){
            strcpy(res[i], "yes");
        } else{
            strcpy(res[i], "no");
        }
    
     }
    
    for(int i = 0; i < qntdNums; i++){
        printf("%s ", res[i]);
        free(res[i]);
    }
    
    free(res);

}