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
            if(color[i] == 0) {
                colorize(g, i, !c);
            } else if(color[i] == c) {
                fail = 1;
                return;
            }
        }
    }
}

void tach(Graph *g) {
    for(int i=1; i<=g->n; i++) {
        color[i] = 0;
    }
    fail = 0;
    colorize(g, 1, 1);
    if(fail != 0) printf("IMPOSSIBLE");
    else {
        for(int i=1; i<=g->n; i++) {
            if(color[i] == 1) printf("%d ", i);
        }
        printf("\n");
        for(int i=1; i<=g->n; i++) {
            if(color[i] != 1) printf("%d ", i);
        }
    }
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
    tach(&g);
}