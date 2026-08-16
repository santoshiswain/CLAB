#include <stdio.h>

#define MAX 128

void add(int A[MAX][MAX], int B[MAX][MAX],
         int C[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int A[MAX][MAX], int B[MAX][MAX],
              int C[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void multiplySpecial(int A[MAX][MAX], int B[MAX][MAX],
                     int C[MAX][MAX], int n)
{
    // Base case
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int A1[MAX][MAX], A2[MAX][MAX];
    int B1[MAX][MAX], B2[MAX][MAX];

    int Ap[MAX][MAX], Am[MAX][MAX];
    int Bp[MAX][MAX], Bm[MAX][MAX];

    int P[MAX][MAX], Q[MAX][MAX];

    int C1[MAX][MAX], C2[MAX][MAX];

    // Extract A1, A2, B1, B2
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {

            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];

            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
        }
    }

    /*
        Ap = A1 + A2
        Am = A1 - A2

        Bp = B1 + B2
        Bm = B1 - B2
    */

    add(A1, A2, Ap, k);
    subtract(A1, A2, Am, k);

    add(B1, B2, Bp, k);
    subtract(B1, B2, Bm, k);

    // Only TWO recursive multiplications
    multiplySpecial(Ap, Bp, P, k);
    multiplySpecial(Am, Bm, Q, k);

    /*
        C1 = (P + Q) / 2
        C2 = (P - Q) / 2
    */

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {

            C1[i][j] = (P[i][j] + Q[i][j]) / 2;
            C2[i][j] = (P[i][j] - Q[i][j]) / 2;
        }
    }

    // Combine
    /*
          C = | C1 C2 |
              | C2 C1 |
    */

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {

            C[i][j] = C1[i][j];
            C[i][j + k] = C2[i][j];

            C[i + k][j] = C2[i][j];
            C[i + k][j + k] = C1[i][j];
        }
    }
}

int main()
{
    int n;

    int A[MAX][MAX];
    int B[MAX][MAX];
    int C[MAX][MAX];

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter Matrix A:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter Matrix B:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    multiplySpecial(A, B, C, n);

    printf("\nResult Matrix:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}