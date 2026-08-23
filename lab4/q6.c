#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int point;
    int type;       // +1 = start, -1 = end
} Event;

int compare(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->point != e2->point)
        return e1->point - e2->point;

    // Start comes before end because endpoints are included
    return e2->type - e1->type;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Event events[2 * n];

    for (int i = 0; i < n; i++)
    {
        int l, r;

        printf("Enter interval %d: ", i + 1);
        scanf("%d %d", &l, &r);

        events[2 * i].point = l;
        events[2 * i].type = 1;

        events[2 * i + 1].point = r;
        events[2 * i + 1].type = -1;
    }

    // Sort all events
    qsort(events, 2 * n, sizeof(Event), compare);

    int count = 0;
    int maxCount = 0;
    int p = 0;

    for (int i = 0; i < 2 * n; i++)
    {
        count += events[i].type;

        if (count > maxCount)
        {
            maxCount = count;
            p = events[i].point;
        }
    }

    printf("\nPoint with maximum overlap = %d\n", p);
    printf("Maximum number of intervals = %d\n", maxCount);

    return 0;
}