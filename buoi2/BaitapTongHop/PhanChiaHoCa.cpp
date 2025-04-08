#include <stdio.h>
#define max 100

typedef struct {
    int n;
    int A[max][max];
} Graph;

void init_graph(Graph *g, int n) {
    g->n = n;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) g->A[i][j] = 0;
    }
}

void add_edge(Graph *g, int u, int v) {
    g->A[u][v] = 1;
    g->A[v][u] = 1;
}

int color[max];
int fail;

void colorize(Graph *g, int u, int c) {
    color[u] = c;
    for(int i=1; i<=g->n; i++) {
        if(g->A[u][i] != 0) {
            if(color[i] == 0) colorize(g, i, !c);
            else if(color[i] == c) {
                fail = 1;
                return;
            }
        }
    }
}

int phanDoi(Graph *g) {
    for(int i=1; i<=g->n; i++) {
        color[i] = 0;
    }
    fail = 0;
    int l = 0;
    for(int i=1; i<=g->n; i++) {
        for(int j=1; j<=g->n; j++) {
            if(g->A[i][j] != 0 && l == 0) {
                colorize(g, i, 1);
                l++;
            }
        }
    }
    return fail;
}

int main() {
    Graph g;
    int dinh, canh;
    scanf("%d%d", &dinh, &canh);
    init_graph(&g, dinh);
    for(int i=1; i<=canh; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&g, u, v);
    }
    if(phanDoi(&g) != 0) printf("-1 -1");
    else {
        int c1 = 0, c2 = 0;
        for(int i=1; i<=g.n; i++) {
            if(color[i] == 1) c1++;
            else c2++;
        }
        printf("%d %d", c1, c2);
    }
}