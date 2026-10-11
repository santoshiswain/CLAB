
#include <stdio.h>

#define MAX 1000

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapify(int a[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1, r = 2 * i + 2;

    if (l < n && a[l] > a[largest])
        largest = l;
    if (r < n && a[r] > a[largest])
        largest = r;

    if (largest != i) {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}

void insert(int a[], int *n, int x) {
    int i = (*n)++;
    a[i] = x;

    while (i > 0 && a[(i - 1) / 2] < a[i]) {
        swap(&a[i], &a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extractMax(int a[], int *n) {
    int x = a[0];
    a[0] = a[--(*n)];
    heapify(a, *n, 0);
    return x;
}

int main() {
    int a[MAX], n, minVal = 1000000000;
    int deviation;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter positive integers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);

        if (a[i] % 2 != 0)
            a[i] *= 2;

        if (a[i] < minVal)
            minVal = a[i];
    }

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    deviation = a[0] - minVal;

    while (a[0] % 2 == 0) {
        int x = extractMax(a, &n);
        x /= 2;

        if (x < minVal)
            minVal = x;

        insert(a, &n, x);

        int current = a[0] - minVal;
        if (current < deviation)
            deviation = current;
    }

    printf("Minimum deviation = %d\n", deviation);
    return 0;
}
