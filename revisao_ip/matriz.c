#include <stdio.h>
#include <stdlib.h>

int main(){

    int m, n, i, j, k;
    scanf("%d %d", &m, &n); 

    int **matA = (int **) calloc(m, sizeof(int *));
    int **matB = (int **) calloc(m, sizeof(int *));
    int **matRes = (int **) calloc(m, sizeof(int *));
    for (i = 0; i < m; i++) {
        matA[i] = (int *)calloc(n, sizeof(int));
        matB[i] = (int *)calloc(n, sizeof(int));
        matRes[i] = (int *)calloc(n, sizeof(int));
    }

    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            int atNum; scanf("%d", &atNum);
            matA[i][j] = atNum; 
        }
    }
    char op; scanf(" %c", &op);

    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            int atNum2; scanf("%d", &atNum2);
            matB[i][j] = atNum2; 
        }
    }

    if(op == '+'){
        for(i = 0; i < m; i++){
            for(j = 0; j < n; j++){
                matRes[i][j] = matA[i][j] + matB[i][j]; 
            }
        }
    } else if(op == 'x'){
        if(m == n){
            for(i = 0; i < m; i++){
                for(j = 0; j < n; j++){
                    for(k = 0; k < n; k++) {
                        matRes[i][j] += matA[i][k] * matB[k][j];
                    }                
                }
            }
        } else{
            printf("ERROR");
        }
    } 

    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            printf("%d ", matRes[i][j]); 
        }
        printf("\n");
    }

    free(matA);
    free(matB);
    free(matRes);

}