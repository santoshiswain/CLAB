#include <stdio.h>
long long min_moves_to_invert_triangle(long long n) {
    if (n < 1) return 0;
    return (n * (n + 1)) / 6;
}

int main(void) {
    printf("Rows (n) | Total Coins | Minimum Moves\n");
    for (long long n = 1; n <= 10; n++) {
        long long total_coins = (n * (n + 1)) / 2;
        long long moves = min_moves_to_invert_triangle(n);
        printf("%8lld | %11lld | %13lld\n", n, total_coins, moves);
    }
    return 0;
}