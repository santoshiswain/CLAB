#include <stdio.h>

void merge(int a[], int b[], int result[], int n1, int n2)
{
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2)
    {
        if (a[i] <= b[j])
            result[k++] = a[i++];
        else
            result[k++] = b[j++];
    }

    while (i < n1)
        result[k++] = a[i++];

    while (j < n2)
        result[k++] = b[j++];
}

int main()
{
    int k, n;

    printf("Enter number of arrays: ");
    scanf("%d", &k);

    printf("Enter size of each array: ");
    scanf("%d", &n);

    int arr[k][k * n];

    // Input arrays
    printf("Enter %d sorted arrays:\n", k);
    for (int i = 0; i < k; i++)
    {
        printf("Array %d: ", i + 1);
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    int current = k;
    int currentSize = n;
    // Repeat until only one array remains
    while (current > 1)
    {
        int newCount = 0;
        for (int i = 0; i < current; i += 2)
        {
            if (i + 1 < current)
            {
                merge(arr[i],
                      arr[i + 1],
                      arr[newCount],
                      currentSize,
                      currentSize);

                newCount++;
            }
            else
            {
                // If odd number of arrays, copy the last one
                for (int j = 0; j < currentSize; j++)
                    arr[newCount][j] = arr[i][j];

                newCount++;
            }
        }

        current = newCount;
        currentSize *= 2;
    }
    printf("\nFinal merged array:\n");
    for (int i = 0; i < k * n; i++)
    {
        printf("%d ", arr[0][i]);
    }
    return 0;
}