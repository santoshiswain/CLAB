
#include <stdio.h>
#include <math.h>

int main() {
    double n;

    printf("Enter the value of n: ");
    scanf("%lf", &n);

    int i, j;

    double arr[3][4] = {
        {n * log2(n), 12 * pow(n, 0.5), 1 / n, pow(n, log2(n))},
        {100 * pow(n, n) + 6 * n, pow(n, 0.51), pow(n, n) - 324, 50 * pow(n, 0.5)},
        {2 * n * n * n, pow(3, n), pow(2, 32) * n, log2(n)}
    };

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            printf("%lf ", arr[i][j] );
            printf("\n");

        }
        printf("\n");
    }

    return 0;
}