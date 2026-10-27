#include <stdio.h>

int head[1000], nxt[20000], to[20000], ec = 0;
int parent[1000], sz[1000], active[1000], order[1000];
long long w[1000], sum[1000], ans[1000];

void addEdge(int a, int b) {
    to[ec] = b;
    nxt[ec] = head[a];
    head[a] = ec;
    ec++;
}

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int main() {
    int V, E, i, e;

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);
    printf("Enter vertex values: ");
    for (i = 0; i < V; i++) {
        scanf("%lld", &w[i]);
        head[i] = -1;
        parent[i] = i;
        sz[i] = 1;
        sum[i] = w[i];
        active[i] = 0;
    }

    printf("Enter edges (u v), vertices 0 to %d:\n", V - 1);
    for (i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    printf("Enter deletion order: ");
    for (i = 0; i < V; i++)
        scanf("%d", &order[i]);

    long long best = 0;
    for (i = V - 1; i >= 0; i--) {
        ans[i] = best;
        int v = order[i];
        active[v] = 1;
        for (e = head[v]; e != -1; e = nxt[e]) {
            int u = to[e];
            if (!active[u]) continue;
            int a = find(v);
            int b = find(u);
            if (a != b) {
                if (sz[a] < sz[b]) {
                    int t = a;
                    a = b;
                    b = t;
                }
                parent[b] = a;
                sz[a] += sz[b];
                sum[a] += sum[b];
            }
        }
        int r = find(v);
        if (sum[r] > best) best = sum[r];
    }

    for (i = 0; i < V; i++)
        printf("After deleting vertex %d: max component sum = %lld\n", order[i], ans[i]);
    return 0;
}
