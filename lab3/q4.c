#include <stdio.h>

#define MAX 100

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

void strassen(int A[MAX][MAX], int B[MAX][MAX],
              int C[MAX][MAX], int n)
{
    // Base case
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int A11[MAX][MAX], A12[MAX][MAX];
    int A21[MAX][MAX], A22[MAX][MAX];

    int B11[MAX][MAX], B12[MAX][MAX];
    int B21[MAX][MAX], B22[MAX][MAX];

    int M1[MAX][MAX], M2[MAX][MAX];
    int M3[MAX][MAX], M4[MAX][MAX];
    int M5[MAX][MAX], M6[MAX][MAX];
    int M7[MAX][MAX];

    int temp1[MAX][MAX];
    int temp2[MAX][MAX];

    // Divide A and B into 4 submatrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {

            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // M1 = (A11 + A22)(B11 + B22)
    add(A11, A22, temp1, k);
    add(B11, B22, temp2, k);
    strassen(temp1, temp2, M1, k);

    // M2 = (A21 + A22)B11
    add(A21, A22, temp1, k);
    strassen(temp1, B11, M2, k);

    // M3 = A11(B12 - B22)
    subtract(B12, B22, temp1, k);
    strassen(A11, temp1, M3, k);

    // M4 = A22(B21 - B11)
    subtract(B21, B11, temp1, k);
    strassen(A22, temp1, M4, k);

    // M5 = (A11 + A12)B22
    add(A11, A12, temp1, k);
    strassen(temp1, B22, M5, k);

    // M6 = (A21 - A11)(B11 + B12)
    subtract(A21, A11, temp1, k);
    add(B11, B12, temp2, k);
    strassen(temp1, temp2, M6, k);

    // M7 = (A12 - A22)(B21 + B22)
    subtract(A12, A22, temp1, k);
    add(B21, B22, temp2, k);
    strassen(temp1, temp2, M7, k);

    int C11[MAX][MAX], C12[MAX][MAX];
    int C21[MAX][MAX], C22[MAX][MAX];

    // C11 = M1 + M4 - M5 + M7
    add(M1, M4, temp1, k);
    subtract(temp1, M5, temp2, k);
    add(temp2, M7, C11, k);

    // C12 = M3 + M5
    add(M3, M5, C12, k);

    // C21 = M2 + M4
    add(M2, M4, C21, k);

    // C22 = M1 - M2 + M3 + M6
    subtract(M1, M2, temp1, k);
    add(temp1, M3, temp2, k);
    add(temp2, M6, C22, k);

    // Combine submatrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {

            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

int main()
{
    int n;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

    printf("Enter size of matrix: ");
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

    strassen(A, B, C, n);

    printf("\nResult Matrix:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}