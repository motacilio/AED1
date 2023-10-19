#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){

    int i, j, qntdNums; 
    scanf("%d", &qntdNums);

    char **listaNums = (char **) malloc(qntdNums * sizeof(char *));
    for(i=0; i < qntdNums; i++){
        listaNums[i] = (char *) malloc(9 * sizeof(char));
    }

    for(i = 0; i < qntdNums; i++){
        double numAtual; scanf("%lf", &numAtual);
        int auxDivisores = 0;
        double raiz = sqrt(numAtual);

        for(j = 1; j <= raiz; j++){
            if((int) numAtual % j == 0){
                auxDivisores++;
            }
        }

        if(auxDivisores <= 1){
            listaNums[i] = "primo";
        } else {
            listaNums[i] = "composto";
        }
    } 

    for(i = 0; i < qntdNums; i++){
        printf("%s\n", listaNums[i]);
    }   

}