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

int deg(Graph *g, int x) {
    int cnt = 0;
    for(int i=1; i<=g->n; i++) {
        if(g->A[x][i] != 0 && x != i) cnt++;
    }
    return cnt;
}

int main() {
    Graph g;
    int dinh, canh;
    scanf("%d%d", &dinh, &canh);
    init_graph(&g, dinh);
    for(int i=0; i<canh; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&g, u, v);
    }
    for(int i=1; i<=g.n; i++) {
        printf("%d\n", deg(&g, i));
    }
}