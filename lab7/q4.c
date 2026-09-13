#include <stdio.h>
#include <stdlib.h>

void solve(int n, int a[]) {
    if (n == 1) {
        if (a[0]) {
            a[0] = 0;
            printf("Toggle switch 1\n");
        }
        return;
    }

    if (a[n - 1]) {
        a[n - 1] = 0;
        printf("Toggle switch %d\n", n);
    }

    for (int i = n - 2; i >= 0; i--) {
        if (a[i]) {
            a[i + 1] = 1;
            printf("Toggle switch %d\n", i + 2);

            a[i] = 0;
            printf("Toggle switch %d\n", i + 1);

            a[i + 1] = 0;
            printf("Toggle switch %d\n", i + 2);
        }
    }
}

int main() {
    int n;

    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        a[i] = 1;

    solve(n, a);

    free(a);
    return 0;
}