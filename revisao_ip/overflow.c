#include <stdio.h>
#include <stdlib.h>

int main(){
    
    int numMax, num1, num2, resultado;
    char oper;
    scanf("%d", &numMax);

    scanf("%d %c %d", &num1, &oper, &num2);

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