#include <stdio.h>

int Fibbonaci(int n);

int main(){

    int n; scanf("%d", &n);
    int i;

    for(i = 0; i<=n; i++){
        int resultado;
        resultado = Fibbonaci(i);
        printf("%d ", resultado);
    }
    
}

int Fibbonaci(int n){
    if(n == 0){
        return 0;
    } else if(n == 1 || n == 2){
        return 1;
    } else if(n > 2){
        return Fibbonaci(n - 1) + Fibbonaci(n - 2);
    }
    return 0;
}