#include <stdio.h>
#include <math.h>
int get_optimal_k(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return (int)(n + 1 - round(sqrt(2 * n + 1)));
}
long long hanoi_3pegs(int k, char src, char dst, char aux, long long *move_count) {
    if (k == 0) return 0;
    
    hanoi_3pegs(k - 1, src, aux, dst, move_count);
    (*move_count)++;
    hanoi_3pegs(k - 1, aux, dst, src, move_count);
    return *move_count;
}
void reves_puzzle(int n, char src, char dst, char aux1, char aux2, long long *move_count) {
    if (n == 0) return;
    if (n == 1) {
        (*move_count)++;
        return;
    }
    int k = get_optimal_k(n);
    reves_puzzle(n - k, src, aux1, aux2, dst, move_count);
    hanoi_3pegs(k, src, dst, aux2, move_count);
    reves_puzzle(n - k, aux1, dst, src, aux2, move_count);
}

int main(void) {
    int test_disks[] = {1, 3, 8, 10, 15};
    int num_tests = sizeof(test_disks) / sizeof(test_disks[0]);
    printf("%-8s | %-12s | %-12s\n", "Disks(n)", "Optimal k", "Total Moves");
    for (int i = 0; i < num_tests; i++) {
        int n = test_disks[i];
        long long move_count = 0;
        int k = get_optimal_k(n);
        reves_puzzle(n, 'A', 'D', 'B', 'C', &move_count);
        printf("%-8d | %-12d | %-12lld\n", n, k, move_count);
    }

    return 0;
}