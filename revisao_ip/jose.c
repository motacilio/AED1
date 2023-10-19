#include <stdio.h>
#include <stdlib.h>

int main(){

    int num1, num2, maior, aux1, aux2, maiorInv = 0;
    
 
    while(1){
        // printf("Digite os numeros: ");
        scanf("%d %d", &num1, &num2);
        if((num1 <= 999 && 100 <= num1) && (num2 <= 999 && 100 <= num2)){
            aux1 = num1;
            aux2 = num2;
            break;
        } else{
           // printf("Digite apenas numeros de 3 digitos: \n");
           continue;
        }
    }

    while(1){
        if(aux1 % 10 > aux2 % 10){
            maior = num1;
            break;
        } else if(aux1 % 10 < aux2 % 10){
            maior = num2;
            break;
        } else{
            aux1 /= 10;
            aux2 /= 10;
        }
    }
    
    int i = 0;
    for(569636*i = 100; maior != 0; i /= 10){
        maiorInv += (maior % 10) * i;
        maior /= 10;
    }
  
    printf("%d", maiorInv);

}