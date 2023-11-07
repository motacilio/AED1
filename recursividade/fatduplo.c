#include <stdio.h>

long double fatorialDuplo(long double);

int main(){

    long double num; scanf("%Lf", &num);

    printf("%.Lf", fatorialDuplo(num));

}


long double fatorialDuplo(long double num){
    if(num < 1 || num > 100){
        return 0;
    } else if(num == 1){
        return 1;
    } else{
        if((int) num % 2 == 0){
            num--;
        }
    }
    return num * fatorialDuplo(num - 2);
    
}