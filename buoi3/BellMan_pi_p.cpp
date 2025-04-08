#include <stdio.h>
#define max 100

typedef struct {
    int u, v, e;
} Edge;

typedef struct {
    int n, m;
    Edge edges[max];
} Graph;

void init_graph(Graph *g, int n) {
    g->n = n;
    g->m = 0;
}

void add_edge(Graph *g, int u, int v, int e) {
    g->edges[g->m].u = u;
    g->edges[g->m].v = v;
    g->edges[g->m].e = e;
    g->m++;
}

int pi[max], p[max];

void BellMan(Graph *g, int x) {
    for(int i=1; i<=g->n; i++) {
        pi[i] = max;
        p[i] = -1;
    }
    pi[x] = 0;
    for(int i=1; i<=g->n; i++) {
        for(int j=0; j<g->m; j++) {
            int u = g->edges[j].u;
            int v = g->edges[j].v;
            int e = g->edges[j].e;
            if(pi[u] + e < pi[v]) {
                pi[v] = pi[u] + e;
                p[v] = u;
            }
        }
    }
}

int main() {
    Graph g;
    int dinh, canh;
    scanf("%d%d", &dinh, &canh);
    init_graph(&g, dinh);
    for(int i=0; i<canh; i++) {
        int u, v, e;
        scanf("%d%d%d", &u, &v, &e);
        add_edge(&g, u, v, e);
    }
    BellMan(&g, 1);
    for(int i=1; i<=g.n; i++) {
        printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
    }
}