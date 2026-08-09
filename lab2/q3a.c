#include <stdio.h>
#include <stdlib.h>

void merge(int a[], int b[], int result[], int n1, int n2) {
    int i = 0, j = 0, k = 0;

    // Merge two sorted arrays
    while (i < n1 && j < n2) {
        if (a[i] <= b[j]) {
            result[k] = a[i];
            i++;
        } else {
            result[k] = b[j];
            j++;
        }
        k++;
    }

    // Remaining elements of a
    while (i < n1) {
        result[k] = a[i];
        i++;
        k++;
    }

    // Remaining elements of b
    while (j < n2) {
        result[k] = b[j];
        j++;
        k++;
    }
}

int main() {
    int k, n;

    printf("Enter number of arrays: ");
    scanf("%d", &k);

    printf("Enter number of elements in each array: ");
    scanf("%d", &n);

    int arr[k][n];

    printf("Enter sorted arrays:\n");

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    // Initially result contains the first array
    int size = n;
    int *result = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        result[i] = arr[0][i];
    }

    // Merge result with every next array
    for (int i = 1; i < k; i++) {

        int newSize = size + n;

        int *newResult = malloc(newSize * sizeof(int));

        merge(result, arr[i], newResult, size, n);

        free(result);

        result = newResult;
        size = newSize;
    }

    printf("\nMerged sorted array:\n");

    for (int i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }

    free(result);

    return 0;
}