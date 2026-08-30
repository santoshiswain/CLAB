#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return i + 1;
}

int quickSelect(int arr[], int low, int high, int k)
{
    if (low == high)
        return arr[low];

    int pivotIndex = partition(arr, low, high);

    int leftSize = pivotIndex - low + 1;

    if (k == leftSize)
        return arr[pivotIndex];

    else if (k < leftSize)
        return quickSelect(arr, low, pivotIndex - 1, k);

    else
        return quickSelect(arr, pivotIndex + 1, high,
                           k - leftSize);
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    double median;

    if (n % 2 == 1)
    {
        median = quickSelect(arr, 0, n - 1, n / 2 + 1);
    }
    else
    {
        int x = quickSelect(arr, 0, n - 1, n / 2);
        int y = quickSelect(arr, 0, n - 1, n / 2 + 1);

        median = (x + y) / 2.0;
    }

    printf("Median = %.2lf\n", median);

    free(arr);

    return 0;
}