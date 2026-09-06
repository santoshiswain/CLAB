#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI acos(-1.0)

/*
    Recursive Divide and Conquer FFT

    a     : input/output array
    n     : size (must be power of 2)
    invert: 0 -> FFT
            1 -> Inverse FFT
*/
void fft(double complex *a, int n, int invert)
{
    /* Base case */
    if (n == 1)
        return;

    /* Divide */
    double complex *even = malloc((n / 2) * sizeof(double complex));
    double complex *odd  = malloc((n / 2) * sizeof(double complex));

    for (int i = 0; i < n / 2; i++)
    {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }

    /* Conquer */
    fft(even, n / 2, invert);
    fft(odd, n / 2, invert);

    double angle = 2 * PI / n;

    if (!invert)
        angle = -angle;

    double complex w = 1.0;
    double complex wn = cos(angle) + I * sin(angle);

    for (int k = 0; k < n / 2; k++)
    {
        double complex t = w * odd[k];

        a[k] = even[k] + t;
        a[k + n / 2] = even[k] - t;

        w *= wn;
    }

    free(even);
    free(odd);
    
    /* Normalize during inverse FFT */
    if (invert)
    {
        for (int i = 0; i < n; i++)
            a[i] /= 2.0;
    }
}

/*
    Convolution of A and B

    A has length m
    B has length n
*/
void convolution(double *A, int m,
                 double *B, int n,
                 double *C)
{
    int resultSize = m + n - 1;

    /* Find next power of 2 */
    int N = 1;

    while (N < resultSize)
        N *= 2;

    /*
        Allocate complex arrays
        and initialize with zeros
    */
    double complex *FA =
        calloc(N, sizeof(double complex));

    double complex *FB =
        calloc(N, sizeof(double complex));

    /* Copy A and B */
    for (int i = 0; i < m; i++)
        FA[i] = A[i];

    for (int i = 0; i < n; i++)
        FB[i] = B[i];

    /* FFT(A) */
    fft(FA, N, 0);

    /* FFT(B) */
    fft(FB, N, 0);

    /* Point-wise multiplication */
    for (int i = 0; i < N; i++)
        FA[i] = FA[i] * FB[i];

    /* Inverse FFT */
    fft(FA, N, 1);

    /* Extract result */
    for (int i = 0; i < resultSize; i++)
        C[i] = creal(FA[i]);

    free(FA);
    free(FB);
}

int main()
{
    int m, n;

    printf("Enter size of vector A (m): ");
    scanf("%d", &m);

    printf("Enter size of vector B (n): ");
    scanf("%d", &n);

    if (n < m)
    {
        printf("Error: n must be >= m.\n");
        return 1;
    }

    double *A = malloc(m * sizeof(double));
    double *B = malloc(n * sizeof(double));
    double *C = malloc((m + n - 1) * sizeof(double));

    printf("\nEnter elements of A:\n");

    for (int i = 0; i < m; i++)
        scanf("%lf", &A[i]);

    printf("\nEnter elements of B:\n");

    for (int i = 0; i < n; i++)
        scanf("%lf", &B[i]);

    /* Perform convolution */
    convolution(A, m, B, n, C);

    printf("\nConvolution C:\n");

    for (int i = 0; i < m + n - 1; i++)
    {
        /*
            Remove tiny floating-point errors
        */
        if (fabs(C[i]) < 1e-9)
            C[i] = 0;

        printf("C[%d] = %.2lf\n", i, C[i]);
    }

    free(A);
    free(B);
    free(C);

    return 0;
}