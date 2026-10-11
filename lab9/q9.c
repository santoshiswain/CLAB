
#include <stdio.h>
#include <limits.h>

#define MAX 100

int main() {
    int n, w[MAX];
    long long prefix[MAX] = {0};
    long long dp[MAX][MAX];

    printf("Enter number of weights: ");
    scanf("%d", &n);

    printf("Enter weights in order: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
        prefix[i + 1] = prefix[i] + w[i];
    }

    for (int i = 0; i < n; i++)
        dp[i][i] = 0;

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len - 1;
            long long sum = prefix[j + 1] - prefix[i];
            dp[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++) {
                long long cost =
                    dp[i][k] + dp[k + 1][j] + sum;

                if (cost < dp[i][j])
                    dp[i][j] = cost;
            }
        }
    }

    printf("Minimum weighted path length = %lld\n",
           dp[0][n - 1]);

    return 0;
}
