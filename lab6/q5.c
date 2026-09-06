/* Q1. Fibonacci Number using Dynamic Programming */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    scanf("%d", &n);

    long long *dp = (long long *)malloc((n + 1) * sizeof(long long));

    dp[0] = 0;

    if (n >= 1)
        dp[1] = 1;

    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];

    printf("%lld\n", dp[n]);

    free(dp);

    return 0;
}