#include <stdio.h>

int main() {
    int n;

    scanf("%d", &n);

    printf("Shooting sequence:\n");

    for (int i = 2; i <= n - 1; i++)
        printf("%d ", i);

    for (int i = 2; i <= n - 1; i++)
        printf("%d ", i);

    printf("\n");

    return 0;
}