#include <stdio.h>
#include <limits.h>

void printOrder(int i, int j, int n, int bracket[n][n]) {
    if (i == j) {
        printf("A%d", i);
        return;
    }

    printf("(");

    printOrder(i, bracket[i][j], n, bracket);

    printf(" x ");

    printOrder(bracket[i][j] + 1, j, n, bracket);

    printf(")");
}

int main() {
    int n;

    scanf("%d", &n);

    int p[n + 1];

    for (int i = 0; i <= n; i++)
        scanf("%d", &p[i]);

    long long dp[n][n];
    int bracket[n][n];

    for (int i = 1; i < n; i++)
        dp[i][i] = 0;

    for (int length = 2; length < n; length++) {

        for (int i = 1; i < n - length + 1; i++) {

            int j = i + length - 1;

            dp[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++) {

                long long cost =
                    dp[i][k]
                    + dp[k + 1][j]
                    + (long long)p[i - 1] * p[k] * p[j];

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    bracket[i][j] = k;
                }
            }
        }
    }

    printf("Minimum multiplications = %lld\n", dp[1][n - 1]);

    printf("Optimal order = ");
    printOrder(1, n - 1, n, bracket);

    printf("\n");

    return 0;
}