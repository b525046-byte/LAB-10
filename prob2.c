#include <stdio.h>

int parent[10000], sz[10000], land[10000];

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int main() {
    int R, C, k, i, d;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    printf("Enter rows, columns and number of operations: ");
    scanf("%d %d %d", &R, &C, &k);
    for (i = 0; i < R * C; i++) {
        parent[i] = i;
        sz[i] = 1;
        land[i] = 0;
    }

    int islands = 0;
    printf("Enter land positions (r c), 0-based:\n");
    for (i = 0; i < k; i++) {
        int r, c;
        scanf("%d %d", &r, &c);
        if (r < 0 || r >= R || c < 0 || c >= C) {
            printf("(%d, %d) is outside the grid\n", r, c);
            continue;
        }
        int id = r * C + c;
        if (!land[id]) {
            land[id] = 1;
            islands++;
            for (d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                int nid = nr * C + nc;
                if (!land[nid]) continue;
                int a = find(id);
                int b = find(nid);
                if (a != b) {
                    if (sz[a] < sz[b]) {
                        int t = a;
                        a = b;
                        b = t;
                    }
                    parent[b] = a;
                    sz[a] += sz[b];
                    islands--;
                }
            }
        }
        printf("After adding (%d, %d): %d island(s)\n", r, c, islands);
    }
    return 0;
}
