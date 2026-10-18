
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int parent[MAX], sz[MAX], active[MAX];
long long weight[MAX], sum[MAX], ans[MAX];
int adj[MAX][MAX], deg[MAX];

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

long long getMax(int V) {
    int found = 0;
    long long best = 0;

    for (int i = 0; i < V; i++) {
        if (active[i] && find(i) == i) {
            if (!found || sum[i] > best) {
                best = sum[i];
                found = 1;
            }
        }
    }

    return found ? best : 0;
}

int main() {
    int V, E, u, v;
    int P[MAX];

    printf("Enter vertices and edges: ");
    scanf("%d%d", &V, &E);

    printf("Enter vertex weights:\n");
    for (int i = 0; i < V; i++) {
        scanf("%lld", &weight[i]);
        parent[i] = i;
        sz[i] = 1;
        sum[i] = weight[i];
        active[i] = 0;
        deg[i] = 0;
    }

    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d%d", &u, &v);
        adj[u][deg[u]++] = v;
        adj[v][deg[v]++] = u;
    }

    printf("Enter deletion order:\n");
    for (int i = 0; i < V; i++)
        scanf("%d", &P[i]);

    for (int i = V - 1; i >= 0; i--) {
        ans[i] = getMax(V);

        int x = P[i];
        active[x] = 1;
        parent[x] = x;
        sz[x] = 1;
        sum[x] = weight[x];

        for (int j = 0; j < deg[x]; j++) {
            int y = adj[x][j];

            if (active[y])
                unite(x, y);
        }
    }

    printf("Maximum component weight after each deletion:\n");
    for (int i = 0; i < V; i++)
        printf("%lld ", ans[i]);

    printf("\n");
    return 0;
}
