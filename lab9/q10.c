
#include <stdio.h>
#include <string.h>

#define MAX 100
#define LEN 10000

int overlap(char a[], char b[]) {
    int n = strlen(a);
    int m = strlen(b);
    int limit = n < m ? n : m;

    for (int k = limit; k > 0; k--) {
        if (strncmp(a + n - k, b, k) == 0)
            return k;
    }

    return 0;
}

void merge(char a[], char b[], char result[]) {
    int k = overlap(a, b);

    strcpy(result, a);
    strcat(result, b + k);
}

int main() {
    char s[MAX][LEN];
    char result[LEN];
    int n;

    printf("Enter number of strings: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of strings.\n");
        return 1;
    }

    printf("Enter the strings:\n");
    for (int i = 0; i < n; i++)
        scanf("%9999s", s[i]);

    // Remove strings already contained in another string.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && s[i][0] != '\0' &&
                strstr(s[j], s[i]) != NULL) {
                s[i][0] = '\0';
                break;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (s[i][0] != '\0') {
            strcpy(s[count++], s[i]);
        }
    }

    while (count > 1) {
        int bestI = 0, bestJ = 1;
        int bestOverlap = -1;

        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                if (i == j)
                    continue;

                int k = overlap(s[i], s[j]);

                if (k > bestOverlap) {
                    bestOverlap = k;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        merge(s[bestI], s[bestJ], result);
        strcpy(s[bestI], result);

        for (int j = bestJ; j < count - 1; j++)
            strcpy(s[j], s[j + 1]);

        count--;
    }

    printf("Greedy superstring: %s\n", s[0]);
    printf("Length: %zu\n", strlen(s[0]));

    return 0;
}
