#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, i, j;
    scanf("%d %d", &n, &m);

    int *familias = (int *)calloc(n + 1, sizeof(int)); // Inicialmente, cada pessoa representa uma família

    for (i = 1; i <= n; i++) {
        familias[i] = i; // Cada pessoa pertence a sua própria família inicialmente
    }

    for (i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        int familiaA = familias[a];
        int familiaB = familias[b];

        // Verifica se as duas pessoas pertencem a famílias diferentes
        if (familiaA != familiaB) {
            // Une as famílias em uma única família
            for (j = 1; j <= n; j++) {
                if (familias[j] == familiaB) {
                    familias[j] = familiaA;
                }
            }
        }
    }

    // Conta o número de famílias distintas
    int numFamilies = 0;
    for (i = 1; i <= n; i++) {
        if (familias[i] == i) {
            numFamilies++;
        }
    }

    printf("%d", numFamilies);

    free(familias);

    return 0;
}
