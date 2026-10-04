#include <stdio.h>
#include <stdlib.h>

void collatz(unsigned long long n)
{
    unsigned long long steps = 0;

    printf("Starting value: %llu\n", n);
    printf("Trajectory:\n");

    while (n != 1)
    {
        printf("%llu ", n);

        if (n % 2 == 0)
            n = n / 2;
        else
            n = 3 * n + 1;

        steps++;
    }

    printf("1\n");
    printf("Number of steps = %llu\n", steps);
}

void analyzeInterval(unsigned long long a,
                     unsigned long long b)
{
    unsigned long long n;

    printf("\nCollatz analysis from %llu to %llu\n", a, b);

    for (n = a; n <= b; n++)
    {
        unsigned long long x = n;
        unsigned long long steps = 0;

        while (x != 1)
        {
            if (x % 2 == 0)
                x = x / 2;
            else
                x = 3 * x + 1;

            steps++;
        }

        printf("n = %llu -> steps = %llu\n", n, steps);

        if (n == b)
            break;
    }
}

int main()
{
    int choice;

    printf("1. Analyze single value\n");
    printf("2. Analyze interval\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        unsigned long long n;

        printf("Enter starting value n: ");
        scanf("%llu", &n);

        if (n == 0)
        {
            printf("Enter a positive integer.\n");
            return 0;
        }

        collatz(n);
    }
    else if (choice == 2)
    {
        unsigned long long a, b;

        printf("Enter interval [a, b]: ");
        scanf("%llu %llu", &a, &b);

        if (a == 0 || a > b)
        {
            printf("Invalid interval.\n");
            return 0;
        }

        analyzeInterval(a, b);
    }
    else
    {
        printf("Invalid choice.\n");
    }

    return 0;
}