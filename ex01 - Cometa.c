#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define YEAR 1986

int main(){


    int A;
    int nextYear = YEAR;

    printf("Digite um ano:");
    scanf("%d", &A);

    /*
    if(0 <= A <= pow(10, 4)){ 
        printf("Digite um ano válido");        
    }
   */

  if(A > YEAR){
    while(A > nextYear){
        nextYear += 76;
    }
  } else {
    while(!(A < nextYear && nextYear <= (A + 76))){
        nextYear -= 76;
        
    }
  }
    
    printf("%d", nextYear);


}