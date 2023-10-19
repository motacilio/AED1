#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define YEAR 1986

int main(){


    int A;
    int nextYear = YEAR;
    int auxBiss = 0;

    scanf("%d", &A);

  if(A > YEAR){
    while(A > nextYear){
        nextYear += 76;
        auxBiss += 76;
        if(auxBiss % 1460 == 0){
          nextYear += 1;
        }
    }
  } else {
    while(!(A < nextYear && nextYear <= (A + 76))){
        nextYear -= 76;
        auxBiss += 76;
        if(auxBiss % 1460 == 0){
          nextYear +- 1;
        }
        
    }
  }
    
    printf("%d", nextYear);


}