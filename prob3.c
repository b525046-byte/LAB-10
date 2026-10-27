#include <stdio.h>

int parent[1000], sz[1000];
long long weight[1000];

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int main() {
    int V, K, E, i;

    printf("Enter number of vertices V and size limit K: ");
    scanf("%d %d", &V, &K);
    printf("Enter vertex weights: ");
    for (i = 0; i < V; i++) {
        scanf("%lld", &weight[i]);
        parent[i] = i;
        sz[i] = 1;
    }

    printf("Enter number of edges: ");
    scanf("%d", &E);
    printf("Enter edges (u v w), vertices 0 to %d:\n", V - 1);
    for (i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        int a = find(u);
        int b = find(v);
        if (a != b) {
            if (sz[a] < sz[b]) {
                int t = a;
                a = b;
                b = t;
            }
            parent[b] = a;
            sz[a] += sz[b];
            weight[a] += weight[b];
        }

        long long best = 0;
        for (int j = 0; j < V; j++) {
            if (find(j) == j && sz[j] <= K && weight[j] > best)
                best = weight[j];
        }
        printf("After edge (%d, %d): max weight of a component with size <= %d is %lld\n", u, v, K, best);
    }
    return 0;
}
