#include <stdio.h>

int Maneiras(int S, int notas[], int quantidade[], int index);

int main(){

    int S, N2, N5, N10, N20, N50, N100;
    scanf("%d", &S);
    scanf("%d %d %d %d %d %d", &N2, &N5, &N10, &N20, &N50, &N100);

    int notas[] = {2, 5, 10, 20, 50, 100};
    int quantidade[] = {N2, N5, N10, N20, N50, N100};

    int maneiras = Maneiras(S, notas, quantidade, 5); 
    printf("%d", maneiras);

    return 0;
}

int Maneiras(int S, int notas[], int quantidade[], int index){

    if(S == 0){
        return 1;
    } 
    if(S < 0 || index < 0){
        return 0;
    }

    int maneiras = 0;

    int i;
    for(i = 0; i <= quantidade[index]; i++){
        if(S >= i * notas[index]){
            maneiras += Maneiras(S - i * notas[index], notas, quantidade, index - 1);
        }
    }

    return maneiras;

}