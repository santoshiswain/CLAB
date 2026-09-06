/* Q2. 0/1 Knapsack using Dynamic Programming */

#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    int n, capacity;

    scanf("%d", &n);

    int *weight = (int *)malloc(n * sizeof(int));
    int *profit = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        scanf("%d", &weight[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &profit[i]);

    scanf("%d", &capacity);

    int **dp = (int **)malloc((n + 1) * sizeof(int *));

    for (int i = 0; i <= n; i++)
        dp[i] = (int *)calloc(capacity + 1, sizeof(int));

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (weight[i - 1] <= w)
            {
                dp[i][w] = max(
                    profit[i - 1] + dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    printf("%d\n", dp[n][capacity]);

    for (int i = 0; i <= n; i++)
        free(dp[i]);

    free(dp);
    free(weight);
    free(profit);

    return 0;
}