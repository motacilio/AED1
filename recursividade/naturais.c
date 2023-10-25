#include <stdio.h>

int ImprimirNaturais(int n);

int main(){

    int n; scanf("%d", &n);
    ImprimirNaturais(n);

    return 0;
 
}


int ImprimirNaturais(int n){
    if(n == 0){
        return 0;
    } else if(n > 0) {
        ImprimirNaturais(n - 1);
        printf("%d ", n);
    }
    return 0;
}