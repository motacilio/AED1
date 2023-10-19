#include <stdio.h>
#include <stdlib.h>

int main(){

    int i, j, numPedras, numSapos;

    scanf("%d %d", &numPedras, &numSapos);

    int *pedras = (int *) calloc(numPedras + 1, sizeof(int));

    for(i = 1; i <= numSapos; i++){
        int posSapo; scanf("%d", &posSapo);
        int distSapo; scanf("%d", &distSapo);
        pedras[posSapo] = 1;

        for (j = posSapo; j >= 1; j -= distSapo) {
            pedras[j] = 1;
        }
        for (j = posSapo; j <= numPedras; j += distSapo) {
            pedras[j] = 1;
        }    
    } 

    for(i = 1; i <= numPedras; i++){
        printf("%d\n", pedras[i]);
    }

}