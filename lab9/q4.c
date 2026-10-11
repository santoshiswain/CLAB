
#include <stdio.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapify(int a[], int n, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && a[l] < a[smallest])
        smallest = l;
    if (r < n && a[r] < a[smallest])
        smallest = r;

    if (smallest != i) {
        swap(&a[i], &a[smallest]);
        heapify(a, n, smallest);
    }
}

int extractMin(int a[], int *n) {
    int min = a[0];
    a[0] = a[*n - 1];
    (*n)--;
    heapify(a, *n, 0);
    return min;
}

void insert(int a[], int *n, int x) {
    int i = (*n)++;
    a[i] = x;

    while (i > 0 && a[(i - 1) / 2] > a[i]) {
        swap(&a[i], &a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int main() {
    int a[1000], n;
    long long cost = 0;

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    printf("Enter stick lengths: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    int size = n;

    while (size > 1) {
        int x = extractMin(a, &size);
        int y = extractMin(a, &size);
        int sum = x + y;

        cost += sum;
        insert(a, &size, sum);
    }

    printf("Minimum total cost = %lld\n", cost);
    return 0;
}
