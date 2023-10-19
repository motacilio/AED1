#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define PI 3.14159265

int main(){

    int n, i;
    scanf("%d", &n);

    int *resultados = (int *) calloc(n,  sizeof(int));

    for(i = 0; i < n; i++){

        char fig; scanf(" %c", &fig);
        fig = toupper(fig);

        if(fig == 'C'){
            int raio; scanf("%d", &raio);
            double area = PI * raio * raio;
            resultados[i] = round(area);
            
        } else if(fig == 'E'){
            int raioMaior; scanf("%d", &raioMaior);
            int raioMenor; scanf("%d", &raioMenor);
            double area = PI * raioMaior * raioMenor;
            resultados[i] = round(area);
            
        } else if(fig == 'Z'){
            int baseMaior, baseMenor, altura;
            scanf("%d %d %d", &baseMaior, &baseMenor, &altura);
            double area = ((baseMaior + baseMenor) * altura) / 2;
            resultados[i] = round(area);
        } else if(fig == 'T'){
            int a, b, c; scanf("%d %d %d", &a, &b, &c);
            double semiP = (a + b + c) / 2.0;
            double area = sqrt(semiP*(semiP - a)*(semiP - b)*(semiP - c));
            resultados[i] = round(area);
        }
    }
    
    for(i = 0; i < n; i++){
    printf("%d\n", resultados[i]);
    }
    free(resultados);
}