#include <stdio.h>

int Reverter(int, int);

int main(){

    int n;
    scanf("%d", &n);
    printf("%d", Reverter(n, 0));
    
}

int Reverter(int num, int numInv){   
    if (num == 0){
        return numInv;
    } else{
        numInv =  (numInv * 10) + (num % 10);
        return Reverter(num / 10, numInv);
    } 
}