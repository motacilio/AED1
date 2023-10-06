#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_DIG 41
int main(){

    int t; 

    while(1){         
        scanf("%d", &t);
        if(t >= 1 && t <= 50){
            break;
        } else{
            printf("Teste entre 1 e 50 apenas");
            continue;
        }
    }

    char **resultados = (char **) malloc(t * sizeof(char *));
    
    for(int i = 0; i < t; i++){
        char num1[MAX_DIG];
        char num2[MAX_DIG];

        scanf("%s %s", num1, num2);

        int tam1 = strlen(num1);
        int tam2 = strlen(num2);
        resultados[i] = (char *) malloc(tam1+tam2+1);

        if(strcmp(num1, "0") == 0 || strcmp(num2, "0") == 0){
            strcpy(resultados[i], "0");
            continue;
        }

        for(int j = 0; j < tam1+tam2; j++){
            resultados[i][j] = '0';
        }
        resultados[i][tam1+tam2] = '\0';
        

        for(int j = tam1 - 1; j >= 0; j--){
            for(int k = tam2 - 1; k >= 0; k--){

                int digitoNum1 = num1[j] - '0'; 
                int digitoNum2 = num2[k] - '0';

                int pos1 = k + j;
                int pos2 = k + j + 1;

                int multTemporaria = digitoNum1 * digitoNum2;
                int soma = multTemporaria + (resultados[i][pos2] - '0');
                resultados[i][pos1] += (soma / 10);
                resultados[i][pos2] = (soma % 10) + '0';

            }
        }
    }
    
    for(int j = 0; j < t; j++){
        int comeco = 0;
        while(resultados[j][comeco] == '0' && resultados[j][comeco + 1] != '\0'){
            comeco++;
        }
        printf("%s\n", resultados[j] + comeco);
        free(resultados[j]);
    }

    free(resultados);

    return 0;

}