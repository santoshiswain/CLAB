
#include <stdio.h>

#define MAX 100
#define EPS 1e-9

typedef struct {
    int id;
    double value;
    double weight;
    double lambda;
    double remaining;
    double fraction;
} Item;

int main() {
    Item a[MAX];
    int n;
    double W, time = 0.0, totalValue = 0.0;

    printf("Enter number of items: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of items.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        a[i].id = i + 1;

        printf("Enter value, weight and decay rate for item %d: ",
               i + 1);
        scanf("%lf %lf %lf",
              &a[i].value, &a[i].weight, &a[i].lambda);

        if (a[i].value < 0 || a[i].weight <= 0 ||
            a[i].lambda <= 0) {
            printf("Invalid item data.\n");
            return 1;
        }

        a[i].remaining = a[i].weight;
        a[i].fraction = 0.0;
    }

    printf("Enter knapsack capacity: ");
    scanf("%lf", &W);

    if (W < 0) {
        printf("Invalid capacity.\n");
        return 1;
    }

    double capacity = W;

    printf("\nGreedy selection order:\n");

    while (capacity > EPS) {
        int best = -1;
        double bestDensity = 0.0;

        for (int i = 0; i < n; i++) {
            if (a[i].remaining <= EPS)
                continue;

            double density =
                a[i].value / a[i].weight
                - a[i].lambda * time;

            if (density > bestDensity) {
                bestDensity = density;
                best = i;
            }
        }

        if (best == -1)
            break;

        double take = a[best].remaining;

        if (take > capacity)
            take = capacity;

        double earnedValue = take * bestDensity;

        a[best].remaining -= take;
        a[best].fraction += take / a[best].weight;
        capacity -= take;
        totalValue += earnedValue;

        printf("Time %.2f: Item %d, weight taken %.2f, "
               "density %.2f, value %.2f\n",
               time, a[best].id, take,
               bestDensity, earnedValue);

        time += take;
    }

    printf("\nFraction of each item selected:\n");

    for (int i = 0; i < n; i++) {
        printf("Item %d: %.4f\n",
               a[i].id, a[i].fraction);
    }

    printf("Total weight used: %.2f\n", W - capacity);
    printf("Total value: %.2f\n", totalValue);

    return 0;
}