/* Q4. Matrix Chain Multiplication using Dynamic Programming */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    int N;

    scanf("%d", &N);

    int *arr = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);

    int n = N - 1;

    long long **dp =
        (long long **)malloc((n + 1) * sizeof(long long *));

    for (int i = 0; i <= n; i++)
        dp[i] =
            (long long *)malloc((n + 1) * sizeof(long long));

    /* Cost is zero for multiplying one matrix */
    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;

    /* Chain length */
    for (int length = 2; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            dp[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++)
            {
                long long cost =
                    dp[i][k] +
                    dp[k + 1][j] +
                    (long long)arr[i - 1] *
                    arr[k] *
                    arr[j];

                if (cost < dp[i][j])
                    dp[i][j] = cost;
            }
        }
    }

    printf("%lld\n", dp[1][n]);

    for (int i = 0; i <= n; i++)
        free(dp[i]);

    free(dp);
    free(arr);

    return 0;
}