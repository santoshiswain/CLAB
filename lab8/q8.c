#include <stdio.h>
#include <float.h>

int main()
{
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    int key[n + 1];

    double p[n + 1];
    double q[n + 1];

    printf("Enter sorted keys:\n");

    for (int i = 1; i <= n; i++)
        scanf("%d", &key[i]);

    printf("Enter successful search probabilities p1 to p%d:\n", n);

    for (int i = 1; i <= n; i++)
        scanf("%lf", &p[i]);

    printf("Enter dummy search probabilities q0 to q%d:\n", n);

    for (int i = 0; i <= n; i++)
        scanf("%lf", &q[i]);

    double e[n + 2][n + 1];
    double w[n + 2][n + 1];

    int root[n + 1][n + 1];

    for (int i = 1; i <= n + 1; i++)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int length = 1; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            e[i][j] = DBL_MAX;

            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++)
            {
                double cost = e[i][r - 1] +
                              e[r + 1][j] +
                              w[i][j];

                if (cost < e[i][j])
                {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum Expected Search Cost = %.4lf\n", e[1][n]);

    printf("Root of OBST = Key %d\n", key[root[1][n]]);

    return 0;
}