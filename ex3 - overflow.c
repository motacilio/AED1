#include <stdio.h>
#include <stdlib.h>

int main(){
    
    int numMax, num1, num2, resultado;
    char oper;
    printf("Digite o valor limite: ");
    scanf("%d", &numMax);

    printf("Digite a operacao: ");
    scanf("%d %c %d", &num1, &oper, &num2);

    //printf("%c", oper);

    if(oper == '+'){
        resultado = num1 + num2;
    } else if(oper == 'x'){
        resultado = num1 * num2;
    } 

    if( resultado > numMax){
        printf("overflow");
    } else{
        printf("no overflow");
    }
 

}