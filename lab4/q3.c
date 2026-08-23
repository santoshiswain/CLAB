#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int binarySearch(int arr[], int left, int right, int target)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return 1;

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return 0;
}



int kSum(int arr[], int n, int k, int index, long long sum, int T)
{
    // We have selected k-1 elements
    if (k == 1)
    {
        long long target = (long long)T - sum;

        return binarySearch(arr, index, n - 1, (int)target);
    }

    // Choose the next element
    for (int i = index; i <= n - k; i++)
    {
        if (kSum(arr, n, k - 1, i + 1,
                 sum + arr[i], T))
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    int n, k, T;

    printf("Enter n: ");
    scanf("%d", &n);

    int S[n];

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &S[i]);
    }

    printf("Enter k: ");
    scanf("%d", &k);

    printf("Enter T: ");
    scanf("%d", &T);

    // Sort the set
    mergeSort(S, 0, n - 1);

    if (k < 1 || k > n)
    {
        printf("Invalid value of k\n");
        return 0;
    }

    if (kSum(S, n, k, 0, 0, T))
    {
        printf("Yes, %d elements add up to %d\n", k, T);
    }
    else
    {
        printf("No, %d elements do not add up to %d\n", k, T);
    }

    return 0;
}