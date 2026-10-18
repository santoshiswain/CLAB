
#include <stdio.h>

#define MAX 1000

int parent[MAX], rankArr[MAX], parity[MAX];

int find(int x, int *p) {
    if (parent[x] == x) {
        *p = 0;
        return x;
    }

    int oldParent = parent[x];
    int root = find(oldParent, p);
    *p ^= parity[x];
    parent[x] = root;
    parity[x] = *p;
    return root;
}

int main() {
    int V, E, u, v;
    int pu, pv;

    printf("Enter vertices and number of edges: ");
    scanf("%d%d", &V, &E);

    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rankArr[i] = 0;
        parity[i] = 0;
    }

    printf("Enter edges (u v), vertices numbered 0 to V-1:\n");

    for (int i = 0; i < E; i++) {
        scanf("%d%d", &u, &v);

        int ru = find(u, &pu);
        int rv = find(v, &pv);

        if (ru == rv) {
            if ((pu ^ pv) != 1) {
                printf("Edge (%d,%d) rejected\n", u, v);
                continue;
            }
            printf("Edge (%d,%d) accepted\n", u, v);
        } else {
            if (rankArr[ru] < rankArr[rv]) {
                parent[ru] = rv;
                parity[ru] = pu ^ pv ^ 1;
            } else {
                parent[rv] = ru;
                parity[rv] = pu ^ pv ^ 1;

                if (rankArr[ru] == rankArr[rv])
                    rankArr[ru]++;
            }
            printf("Edge (%d,%d) accepted\n", u, v);
        }
    }

    return 0;
}
