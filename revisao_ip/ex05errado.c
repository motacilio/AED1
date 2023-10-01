#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int conversorQuaternario(int);
int inverteNumero(int);

int main(){

    int numTestes, num;

    scanf("%d", &numTestes);

    char **res = (char **) malloc(numTestes * sizeof(char *));

    for(int i = 0; i < numTestes; i++){
        res[i] = (char *) malloc(5 * sizeof(char));
    }

    for(int i = 0; i < numTestes; i++){
        scanf("%d", &num);
        int numTetra = conversorQuaternario(num);
        int numTetraInv = inverteNumero(numTetra);
        
        while(numTetraInv > 0){
            if(numTetraInv % 10 == 0){
                strcat(res[i], "A");
            } else if(numTetraInv % 10 == 1){
                strcat(res[i], "C");
            } else if(numTetraInv % 10 == 2){
                strcat(res[i], "G");
            } else {
                strcat(res[i], "T");
            }
            numTetraInv /= 10;
        }
    }

    for(int i = 0; i < numTestes; i++){
        printf("%s\n", res[i]);
        free(res[i]);
    }       

    free(res); 
}


int conversorQuaternario(int num){
    int numTetra = 0;

    for(int fator = 1; num > 0; fator *= 10){
        numTetra = numTetra + (num % 4) * fator;
        num /= 4;
        } 

    return numTetra;
}

int inverteNumero(int num){
    int numInv = 0;

    while(num > 0){
        numInv = numInv * 10 + (num % 10);
        num /= 10;
    }
    return numInv; 
}