#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
int egg_drop_classic(int E, int F) {
    int **dp = (int **)malloc((E + 1) * sizeof(int *));
    for (int i = 0; i <= E; i++) {
        dp[i] = (int *)malloc((F + 1) * sizeof(int));
    }
    for (int e = 1; e <= E; e++) {
        dp[e][0] = 0;
        dp[e][1] = 1;
    }
    for (int f = 1; f <= F; f++) {
        dp[1][f] = f;
    }
    for (int e = 2; e <= E; e++) {
        for (int f = 2; f <= F; f++) {
            dp[e][f] = INT_MAX;
            for (int k = 1; k <= f; k++) {
                int broken = dp[e - 1][k - 1];   
                int survived = dp[e][f - k];     
                int worst_case = 1 + MAX(broken, survived);

                if (worst_case < dp[e][f]) {
                    dp[e][f] = worst_case;
                }
            }
        }
    }
    int result = dp[E][F];
    for (int i = 0; i <= E; i++) free(dp[i]);
    free(dp);
    return result;
}
int egg_drop_binary_search(int E, int F) {
    int **dp = (int **)malloc((E + 1) * sizeof(int *));
    for (int i = 0; i <= E; i++) {
        dp[i] = (int *)calloc(F + 1, sizeof(int));
    }
    for (int e = 1; e <= E; e++) dp[e][1] = 1;
    for (int f = 1; f <= F; f++) dp[1][f] = f;
    for (int e = 2; e <= E; e++) {
        for (int f = 2; f <= F; f++) {
            int low = 1, high = f, ans = INT_MAX;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                int broken = dp[e - 1][mid - 1];
                int survived = dp[e][f - mid];
                int worst_case = 1 + MAX(broken, survived);
                if (worst_case < ans) {
                    ans = worst_case;
                }
                if (broken < survived) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            dp[e][f] = ans;
        }
    }
    int result = dp[E][F];
    for (int i = 0; i <= E; i++) free(dp[i]);
    free(dp);
    return result;
}
int main(void) {
    int test_cases[][2] = {
        {2, 100},   
        {3, 14},    
        {4, 500},   
        {5, 1000},  
        {6, 2000}
    };
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    printf("%-8s | %-8s | %-15s\n", "Eggs", "Floors", "Min Drops Needed");
    printf("----------------------------------------\n");
    for (int i = 0; i < num_tests; i++) {
        int e = test_cases[i][0];
        int f = test_cases[i][1];
        int res = egg_drop_binary_search(e, f);
        printf("%-8d | %-8d | %-15d\n", e, f, res);
    }
    return 0;
}