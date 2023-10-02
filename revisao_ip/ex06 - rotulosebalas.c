#include <stdio.h>
#include <stdlib.h>


int main(){

    int qntdRotulos, qntdBalas;

    while(1){
        scanf("%d %d", &qntdRotulos, &qntdBalas);
        if((qntdRotulos <= 1000 && qntdRotulos >= 1) && (qntdBalas >= 1 && qntdBalas <= 20)){
            break;
        }
    }

    int *listaRotulos = (int *) calloc(qntdBalas, sizeof(int));
    
    for(int i = 0; i < qntdRotulos; i++){
        int rotAtual; scanf("%d", &rotAtual);
        listaRotulos[rotAtual]++;
    }

    int envelopes = qntdRotulos;

    for(int i = 1; i <= qntdBalas; i++){
        envelopes = envelopes < listaRotulos[i] ? envelopes : listaRotulos[i];
    }

    printf("%d\n", envelopes);

    free(listaRotulos);
}