/* Q3. Longest Common Subsequence (LCS) using Dynamic Programming */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    char X[1000], Y[1000];

    scanf("%s", X);
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));

    for (int i = 0; i <= m; i++)
        dp[i] = (int *)calloc(n + 1, sizeof(int));

    /* Build LCS table */
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    printf("%d\n", dp[m][n]);

    /* Construct LCS */
    int length = dp[m][n];

    char *lcs = (char *)malloc((length + 1) * sizeof(char));

    lcs[length] = '\0';

    int i = m;
    int j = n;
    int index = length - 1;

    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index] = X[i - 1];
            index--;
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("%s\n", lcs);

    free(lcs);

    for (int i = 0; i <= m; i++)
        free(dp[i]);

    free(dp);

    return 0;
}