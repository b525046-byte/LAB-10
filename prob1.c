#include <stdio.h>

int parent[1000], par[1000], sz[1000];

int find(int x) {
    if (parent[x] == x)
        return x;
    int p = parent[x];
    int root = find(p);
    par[x] = par[x] ^ par[p];
    parent[x] = root;
    return root;
}

int main() {
    int V, E, i;
    int rejected = 0;

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);
    for (i = 0; i < V; i++) {
        parent[i] = i;
        par[i] = 0;
        sz[i] = 1;
    }

    printf("Enter edges (u v), vertices 0 to %d:\n", V - 1);
    for (i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        int ru = find(u);
        int rv = find(v);

        if (ru == rv) {
            if (par[u] == par[v]) {
                printf("Edge (%d, %d): rejected, creates an odd cycle\n", u, v);
                rejected++;
            } else {
                printf("Edge (%d, %d): added\n", u, v);
            }
        } else {
            int link = par[u] ^ par[v] ^ 1;
            if (sz[ru] >= sz[rv]) {
                parent[rv] = ru;
                par[rv] = link;
                sz[ru] += sz[rv];
            } else {
                parent[ru] = rv;
                par[ru] = link;
                sz[rv] += sz[ru];
            }
            printf("Edge (%d, %d): added\n", u, v);
        }
    }
    printf("Edges rejected: %d\n", rejected);
    return 0;
}
