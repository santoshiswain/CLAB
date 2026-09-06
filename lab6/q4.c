#include <stdio.h>
#include <stdlib.h>

/* Reverse A[l ... r] */
void reverse(int *A, int l, int r)
{
    while (l < r)
    {
        int temp = A[l];
        A[l] = A[r];
        A[r] = temp;

        l++;
        r--;
    }
}

/*
    Rotate:

        A B

    into:

        B A

    using three reversals.
*/
void rotate(int *A, int l, int mid, int r)
{
    if (l > mid || mid + 1 > r)
        return;

    reverse(A, l, mid);
    reverse(A, mid + 1, r);
    reverse(A, l, r);
}

/*
    Stable partition.

    Elements <= pivot go before
    elements > pivot.

    Returns the first position of
    the second group.
*/
int stablePartition(int *A, int l, int r, int pivot)
{
    if (l > r)
        return l;

    /* Single element */
    if (l == r)
    {
        if (A[l] <= pivot)
            return l + 1;
        else
            return l;
    }

    int mid = (l + r) / 2;

    /* Partition left half */
    int leftSplit =
        stablePartition(A, l, mid, pivot);

    /* Partition right half */
    int rightSplit =
        stablePartition(A, mid + 1, r, pivot);

    /*
        After recursive calls:

        [L1][H1] [L2][H2]

        Need:

        [L1][L2] [H1][H2]
    */

    if (leftSplit <= mid &&
        rightSplit > mid + 1)
    {
        /*
            H1 = [leftSplit ... mid]
            L2 = [mid+1 ... rightSplit-1]

            Rotate H1 and L2.
        */
        rotate(A,
               leftSplit,
               mid,
               rightSplit - 1);
    }

    /*
        Count elements <= pivot
        in this entire segment.
    */
    int count = 0;

    for (int i = l; i <= r; i++)
    {
        if (A[i] <= pivot)
            count++;
    }

    return l + count;
}

/*
    Sort permutation A[l ... r]

    using divide-and-conquer on value ranges.
*/
void sortByReversal(int *A, int l, int r)
{
    if (l >= r)
        return;

    int minValue = l + 1;
    int maxValue = r + 1;

    int midValue =
        (minValue + maxValue) / 2;

    /*
        Partition values into:

        <= midValue
        >  midValue
    */
    stablePartition(A, l, r, midValue);

    /*
        Find boundary after partition.
    */
    int split = l;

    while (split <= r &&
           A[split] <= midValue)
    {
        split++;
    }

    /*
        Recursively sort both groups.
    */
    if (l < split - 1)
        sortByReversal(A, l, split - 1);

    if (split < r)
        sortByReversal(A, split, r);
}

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    int *A = malloc(n * sizeof(int));

    printf("Enter permutation:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("\nBefore sorting:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    printf("\n");

    sortByReversal(A, 0, n - 1);

    printf("\nAfter sorting:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    printf("\n");

    free(A);

    return 0;
}