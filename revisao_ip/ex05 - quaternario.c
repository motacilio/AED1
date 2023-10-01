#include <stdio.h>
#include <stdlib.h>

int main(){

    int numTestes, i;

    scanf("%d", &numTestes);

    char **res = (char **) malloc(numTestes * sizeof(char *));
    for(int i = 0; i < numTestes; i++){
        res[i] = (char *) malloc(20 * sizeof(char));
    }

    int *numeros = (int *) malloc(numTestes * sizeof(int));
    for(int i = 0; i < numTestes; i++){
        scanf("%d", &numeros[i]);
    }
    

     for(i = 0; i < numTestes; i++){
        int j = 0;
        while (numeros[i] > 0) {
            int resto = numeros[i] % 4;
            char quaternarioChar;
            if (resto == 0) {
                quaternarioChar = 'A';
            } else if (resto == 1) {
                quaternarioChar = 'C';
            } else if (resto == 2) {
                quaternarioChar = 'G';
            } else {
                quaternarioChar = 'T';
            }
            res[i][j] = quaternarioChar;
            numeros[i] /= 4;
            j++;
        }
        res[i][j] = '\0';

        int comeco = 0;
        int fim = j - 1;
        while(comeco < fim){
            char temp = res[i][comeco];
            res[i][comeco] = res[i][fim];
            res[i][fim] = temp;
            comeco++;
            fim--;
        }
    }

    for(int i = 0; i < numTestes; i++){
    printf("%s\n", res[i]);
    free(res[i]);
    }
    
    free(res);
}