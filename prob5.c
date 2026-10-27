#include <stdio.h>
#include <stdlib.h>

int parent[1000], sz[1000], A[1000], root[1000], result[1000];

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int cmpPos(const void *x, const void *y) {
    int a = *(int *)x, b = *(int *)y;
    if (root[a] != root[b]) return root[a] - root[b];
    return a - b;
}

int cmpVal(const void *x, const void *y) {
    int a = *(int *)x, b = *(int *)y;
    if (root[a] != root[b]) return root[a] - root[b];
    return A[a] - A[b];
}

int main() {
    int n, m, i;
    int byPos[1000], byVal[1000];

    printf("Enter n and number of allowed swaps: ");
    scanf("%d %d", &n, &m);
    printf("Enter permutation: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        parent[i] = i;
        sz[i] = 1;
    }

    printf("Enter swaps (u v), positions 1 to %d:\n", n);
    for (i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        int a = find(u - 1);
        int b = find(v - 1);
        if (a != b) {
            if (sz[a] < sz[b]) {
                int t = a;
                a = b;
                b = t;
            }
            parent[b] = a;
            sz[a] += sz[b];
        }
    }

    for (i = 0; i < n; i++) {
        root[i] = find(i);
        byPos[i] = i;
        byVal[i] = i;
    }
    qsort(byPos, n, sizeof(int), cmpPos);
    qsort(byVal, n, sizeof(int), cmpVal);

    for (i = 0; i < n; i++)
        result[byPos[i]] = A[byVal[i]];

    printf("Smallest permutation: ");
    for (i = 0; i < n; i++)
        printf("%d ", result[i]);
    printf("\n");
    return 0;
}
