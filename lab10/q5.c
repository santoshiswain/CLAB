
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int parent[MAX], sz[MAX];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v)
        return;

    if (sz[u] < sz[v]) {
        int t = u;
        u = v;
        v = t;
    }

    parent[v] = u;
    sz[u] += sz[v];
}

int compareInt(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    return (x > y) - (x < y);
}

int main() {
    int n, m, A[MAX], u, v;
    int indices[MAX], values[MAX], result[MAX];

    printf("Enter n and m: ");
    scanf("%d%d", &n, &m);

    printf("Enter permutation:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        parent[i] = i;
        sz[i] = 1;
    }

    printf("Enter allowable swaps (u v):\n");
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        unite(u, v);
    }

    for (int root = 0; root < n; root++) {
        if (find(root) != root)
            continue;

        int count = 0;

        for (int i = 0; i < n; i++) {
            if (find(i) == root) {
                indices[count] = i;
                values[count] = A[i];
                count++;
            }
        }

        qsort(indices, count, sizeof(int), compareInt);
        qsort(values, count, sizeof(int), compareInt);

        for (int i = 0; i < count; i++)
            result[indices[i]] = values[i];
    }

    printf("Lexicographically smallest permutation:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", result[i]);

    printf("\n");
    return 0;
}
