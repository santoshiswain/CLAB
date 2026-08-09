#include <stdio.h>
#include <math.h>

int main() {
    int n;

    printf("Enter value of n: ");
    scanf("%d", &n);

    printf("\nFor n = %d:\n", n);

    printf("1              = %.2lf\n", 1.0);
    printf("log2(n)         = %.2lf\n", log2(n));
    printf("12 * sqrt(n)    = %.2lf\n", 12 * sqrt(n));
    printf("50 * sqrt(n)    = %.2lf\n", 50 * sqrt(n));
    printf("n^0.51          = %.2lf\n", pow(n, 0.51));
    printf("n               = %.2lf\n", (double)n);
    printf("3 * n            = %.2lf\n", 3.0 * n);
    printf("n * log2(n)      = %.2lf\n", n * log2(n));
    printf("n^2 - 324        = %.2lf\n", pow(n, 2) - 324);
    printf("100*n^2 + 6*n    = %.2lf\n",
           100 * pow(n, 2) + 6 * n);
    printf("2*n^3            = %.2lf\n",
           2 * pow(n, 3));
    printf("2^(32*n)         = %.2e\n",
           pow(2, 32.0 * n));

    return 0;
}