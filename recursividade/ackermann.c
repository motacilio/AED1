#include <stdio.h>
#include <stdlib.h>

int akerman(int, int);

int main(){

    int m, n;
    scanf("%d %d", &m, &n);

    printf("%d", akerman(m, n));

}


int akerman(int m, int n){

    if(m == 0){
        return (n + 1);
    } else if(n == 0 && m > 0){
        return akerman(m - 1, 1);
    } else if(m > 0 && n > 0){
        return akerman(m - 1, akerman(m , n - 1));
    }

    return 0;
}