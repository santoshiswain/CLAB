
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int main() {
    int start[MAX], end[MAX], n;
    int i = 0, j = 0, rooms = 0, maximum = 0;

    printf("Enter number of meetings: ");
    scanf("%d", &n);

    printf("Enter start and end time of each meeting:\n");
    for (int k = 0; k < n; k++)
        scanf("%d%d", &start[k], &end[k]);

    qsort(start, n, sizeof(int), compare);
    qsort(end, n, sizeof(int), compare);

    while (i < n) {
        if (start[i] < end[j]) {
            rooms++;
            if (rooms > maximum)
                maximum = rooms;
            i++;
        } else {
            rooms--;
            j++;
        }
    }

    printf("Minimum meeting rooms = %d\n", maximum);
    return 0;
}
