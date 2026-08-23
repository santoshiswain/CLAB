#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int start;
    int end;
} Interval;

// Compare intervals according to starting time
int compare(const void *a, const void *b)
{
    Interval *i1 = (Interval *)a;
    Interval *i2 = (Interval *)b;

    return i1->start - i2->start;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Interval arr[n];

    printf("Enter intervals:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &arr[i].start, &arr[i].end);
    }

    // Sort intervals by starting point
    qsort(arr, n, sizeof(Interval), compare);

    // Merge overlapping intervals
    Interval result[n];
    int count = 0;

    result[count] = arr[0];
    count++;

    for (int i = 1; i < n; i++)
    {
        // Overlapping
        if (arr[i].start <= result[count - 1].end)
        {
            if (arr[i].end > result[count - 1].end)
            {
                result[count - 1].end = arr[i].end;
            }
        }
        else
        {
            // No overlap
            result[count] = arr[i];
            count++;
        }
    }

    printf("\nMerged intervals:\n");

    for (int i = 0; i < count; i++)
    {
        printf("(%d, %d) ", result[i].start, result[i].end);
    }

    printf("\n");

    return 0;
}