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

void add_edge(Graph *g, int u, int v, int e) {
    g->A[u][v] = e;
    g->A[v][u] = e;
}

int pi[max], p[max], mark[max];

void Dijkstra(Graph *g, int x) {
    for(int i=1; i<=g->n; i++) {
        mark[i] = 0;
        pi[i] = max;
        p[i] = -1;
    }
    pi[x] = 0;
    int i = x;
    int temp = 0;
    while(i <= g->n && temp < g->n) {
        int min_pi = max;
        for(int j=1; j<=g->n; j++) {
            if(min_pi > pi[j] && mark[j] == 0) {
                min_pi = pi[j];
                i = j;
            }
        }
        mark[i] = 1;
        for(int j=1; j<=g->n; j++) {
            if(g->A[i][j] != 0) {
                if(pi[i] + g->A[i][j] < pi[j] && mark[j] == 0) {
                    pi[j] = pi[i] + g->A[i][j];
                    p[j] = i;
                }
            }
        }
        temp++;
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
    int s, t;
    scanf("%d%d", &s, &t);
    Dijkstra(&g, s);
    if(pi[t] == max) printf("-1");
    else printf("%d", pi[t]);
}