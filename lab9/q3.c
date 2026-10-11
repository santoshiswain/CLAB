
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    int distance;
    int fuel;
} Station;

Station stations[MAX];
int heap[MAX];
int heapSize = 0;

/* Sort stations by distance */
int compare(const void *a, const void *b) {
    Station *s1 = (Station *)a;
    Station *s2 = (Station *)b;

    if (s1->distance < s2->distance)
        return -1;
    if (s1->distance > s2->distance)
        return 1;
    return 0;
}

/* Insert fuel into max-heap */
void push(int fuel) {
    int i = ++heapSize;
    heap[i] = fuel;

    while (i > 1 && heap[i] > heap[i / 2]) {
        int temp = heap[i];
        heap[i] = heap[i / 2];
        heap[i / 2] = temp;
        i /= 2;
    }
}

/* Remove maximum fuel */
int popMax() {
    int result = heap[1];
    heap[1] = heap[heapSize--];

    int i = 1;

    while (1) {
        int largest = i;
        int left = 2 * i;
        int right = 2 * i + 1;

        if (left <= heapSize &&
            heap[left] > heap[largest])
            largest = left;

        if (right <= heapSize &&
            heap[right] > heap[largest])
            largest = right;

        if (largest == i)
            break;

        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;
        i = largest;
    }

    return result;
}

int main() {
    int n, D, F;

    printf("Enter target distance and initial fuel: ");
    if (scanf("%d %d", &D, &F) != 2 ||
        D < 0 || F < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter number of stations: ");
    if (scanf("%d", &n) != 1 || n < 0 || n > MAX) {
        printf("Invalid number of stations.\n");
        return 1;
    }

    printf("Enter station distance and fuel amount:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%d %d",
                  &stations[i].distance,
                  &stations[i].fuel) != 2 ||
            stations[i].distance < 0 ||
            stations[i].fuel < 0) {
            printf("Invalid station data.\n");
            return 1;
        }
    }

    qsort(stations, n, sizeof(Station), compare);

    long long reach = F;
    int stops = 0;
    int i = 0;

    while (reach < D) {
        /* Add all stations we can currently reach */
        while (i < n && stations[i].distance <= reach) {
            if (stations[i].distance < D)
                push(stations[i].fuel);
            i++;
        }

        /* No reachable station has fuel left to use */
        if (heapSize == 0) {
            printf("Target cannot be reached.\n");
            return 0;
        }

        /* Refuel at the station with the most fuel */
        reach += popMax();
        stops++;
    }

    printf("Minimum refuelling stops: %d\n", stops);

    return 0;
}