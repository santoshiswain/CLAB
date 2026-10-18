
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int parent[MAX], sz[MAX];
long long sum[MAX], weight[MAX];

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
    sum[u] += sum[v];
}

int main() {
    int V, E, K, u, v;

    printf("Enter V, E and K: ");
    scanf("%d%d%d", &V, &E, &K);

    printf("Enter vertex weights:\n");
    for (int i = 0; i < V; i++) {
        scanf("%lld", &weight[i]);
        parent[i] = i;
        sz[i] = 1;
        sum[i] = weight[i];
    }

    printf("Enter edges:\n");

    for (int e = 0; e < E; e++) {
        scanf("%d%d", &u, &v);
        unite(u, v);

        int found = 0;
        long long best = 0;

        for (int i = 0; i < V; i++) {
            if (find(i) == i && sz[i] <= K) {
                if (!found || sum[i] > best) {
                    best = sum[i];
                    found = 1;
                }
            }
        }

        if (found)
            printf("Maximum component weight: %lld\n", best);
        else
            printf("No component satisfies the size constraint\n");
    }

    return 0;
}
