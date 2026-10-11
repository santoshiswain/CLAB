
#include <stdio.h>

int main() {
    int n, rating[1000], candy[1000];
    long long total = 0;

    printf("Enter number of children: ");
    scanf("%d", &n);

    printf("Enter ratings: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &rating[i]);
        candy[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1])
            candy[i] = candy[i - 1] + 1;
    }

    for (int i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1] &&
            candy[i] <= candy[i + 1])
            candy[i] = candy[i + 1] + 1;
    }

    for (int i = 0; i < n; i++)
        total += candy[i];

    printf("Minimum candies = %lld\n", total);
    return 0;
}
