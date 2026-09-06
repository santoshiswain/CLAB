#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Allocate n x n matrix */
double **createMatrix(int n)
{
    double **a = malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
        a[i] = malloc(n * sizeof(double));

    return a;
}

/* Free matrix */
void freeMatrix(double **a, int n)
{
    for (int i = 0; i < n; i++)
        free(a[i]);

    free(a);
}

/* Display matrix */
void displayMatrix(double **a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%8.2lf ", a[i][j]);

        printf("\n");
    }
}

/* (i) Matrix Addition */
void matrixAddition(double **a, double **b, double **c, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] + b[i][j];
    }
}

/* (ii) Matrix Multiplication */
void matrixMultiplication(double **a, double **b, double **c, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = 0;

            for (int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
}

/* (iii) Check Zero Matrix */
int isZeroMatrix(double **a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] != 0)
                return 0;
        }
    }

    return 1;
}

/* (iv) Check Symmetric Matrix */
int isSymmetric(double **a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[i][j] != a[j][i])
                return 0;
        }
    }

    return 1;
}

/* (v) Determinant using Gaussian elimination */
double determinant(double **a, int n)
{
    double **temp = createMatrix(n);

    /* Copy matrix */
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp[i][j] = a[i][j];

    double det = 1.0;

    for (int i = 0; i < n; i++)
    {
        /* Find pivot */
        int pivot = i;

        for (int j = i + 1; j < n; j++)
        {
            if (fabs(temp[j][i]) > fabs(temp[pivot][i]))
                pivot = j;
        }

        /* Singular matrix */
        if (fabs(temp[pivot][i]) < 1e-9)
        {
            freeMatrix(temp, n);
            return 0;
        }

        /* Swap rows */
        if (pivot != i)
        {
            double *swap = temp[i];
            temp[i] = temp[pivot];
            temp[pivot] = swap;

            det = -det;
        }

        det *= temp[i][i];

        /* Eliminate below pivot */
        for (int j = i + 1; j < n; j++)
        {
            double factor = temp[j][i] / temp[i][i];

            for (int k = i + 1; k < n; k++)
                temp[j][k] -= factor * temp[i][k];
        }
    }

    freeMatrix(temp, n);

    return det;
}

/* (vi) Transpose in situ */
void transpose(double **a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double temp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = temp;
        }
    }
}

/*
   (vii) Approximate eigenvalue/eigenvector
   using Power Iteration.

   Finds the dominant (largest magnitude)
   eigenvalue and corresponding eigenvector.
*/
void eigenValueVector(double **a, int n)
{
    double *v = malloc(n * sizeof(double));
    double *next = malloc(n * sizeof(double));

    /* Initial vector */
    for (int i = 0; i < n; i++)
        v[i] = 1.0;

    double eigenvalue = 0;

    int iterations = 1000;

    for (int iteration = 0; iteration < iterations; iteration++)
    {
        /* next = A * v */
        for (int i = 0; i < n; i++)
        {
            next[i] = 0;

            for (int j = 0; j < n; j++)
                next[i] += a[i][j] * v[j];
        }

        /* Find largest component */
        double maxValue = fabs(next[0]);

        for (int i = 1; i < n; i++)
        {
            if (fabs(next[i]) > maxValue)
                maxValue = fabs(next[i]);
        }

        /* Normalize */
        for (int i = 0; i < n; i++)
            v[i] = next[i] / maxValue;

        eigenvalue = maxValue;
    }

    printf("Dominant Eigenvalue = %.6lf\n", eigenvalue);

    printf("Corresponding Eigenvector:\n");

    for (int i = 0; i < n; i++)
        printf("%.6lf\n", v[i]);

    free(v);
    free(next);
}

int main()
{
    int n;

    printf("Enter size of square matrix: ");
    scanf("%d", &n);

    double **A = createMatrix(n);
    double **B = createMatrix(n);
    double **C = createMatrix(n);

    printf("\nEnter elements of Matrix A:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);
    }

    printf("\nEnter elements of Matrix B:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%lf", &B[i][j]);
    }

    /* (i) Addition */
    matrixAddition(A, B, C, n);

    printf("\n(i) Matrix Addition:\n");
    displayMatrix(C, n);

    /* (ii) Multiplication */
    matrixMultiplication(A, B, C, n);

    printf("\n(ii) Matrix Multiplication:\n");
    displayMatrix(C, n);

    /* (iii) Zero matrix */
    printf("\n(iii) Zero Matrix: ");

    if (isZeroMatrix(A, n))
        printf("YES\n");
    else
        printf("NO\n");

    /* (iv) Symmetric */
    printf("\n(iv) Symmetric Matrix: ");

    if (isSymmetric(A, n))
        printf("YES\n");
    else
        printf("NO\n");

    /* (v) Determinant */
    printf("\n(v) Determinant of A = %.4lf\n",
           determinant(A, n));

    /* (vi) Transpose */
    transpose(A, n);

    printf("\n(vi) Transpose of A:\n");
    displayMatrix(A, n);

    /* (vii) Eigenvalue and eigenvector */
    printf("\n(vii) Eigenvalue and Eigenvector of A:\n");
    eigenValueVector(A, n);

    /* Free memory */
    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}