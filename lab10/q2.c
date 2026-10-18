
#include <stdio.h>
#include <stdlib.h>

int *parent, *sz;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

int unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
        return 0;

    if (sz[a] < sz[b]) {
        int temp = a;
        a = b;
        b = temp;
    }

    parent[b] = a;
    sz[a] += sz[b];
    return 1;
}

int main() {
    int R, C, k, r, c, islands = 0;

    printf("Enter rows, columns and operations: ");
    scanf("%d%d%d", &R, &C, &k);

    int N = R * C;

    parent = malloc(N * sizeof(int));
    sz = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        parent[i] = -1;  // Water
        sz[i] = 0;
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < k; i++) {
        scanf("%d%d", &r, &c);

        int id = r * C + c;

        if (parent[id] == -1) {
            parent[id] = id;
            sz[id] = 1;
            islands++;

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr >= 0 && nr < R &&
                    nc >= 0 && nc < C) {
                    int nid = nr * C + nc;

                    if (parent[nid] != -1)
                        islands -= unite(id, nid);
                }
            }
        }

        printf("%d ", islands);
    }

    printf("\n");
    free(parent);
    free(sz);
    return 0;
}
