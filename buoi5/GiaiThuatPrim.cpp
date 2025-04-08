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
}

int pi[max], p[max], mark[max];
void prim(Graph *g, int x) {
    Graph temp;
    init_graph(&temp, g->n);
    int sum = 0;
    for(int i=1; i<=g->n; i++) {
        mark[i] = 0;
        p[i] = -1;
        pi[i] = max;
    }
    pi[x] = 0;
    int i = x;
    int cnt = 0;
    while(i <=g->n && cnt < g->n) {
        int min_pi = max;
        for(int j=1; j<=g->n; j++) {
            if(min_pi > pi[j] && mark[j] == 0) {
                min_pi = pi[j];
                i = j;
            }
        }
        mark[i] = 1;
        if(i != x) {
            add_edge(&temp, p[i], i, min_pi);
        }
        sum += pi[i];
        for(int j=1; j<=g->n; j++) {
            if(g->A[i][j] != 0) {
                if(g->A[i][j] < pi[j] && mark[j] == 0) {
                    pi[j] = g->A[i][j];
                    p[j] = i;
                }
            }
        }
        cnt++;
    }
    printf("%d\n", sum);
    for(int i=1; i<=g->n; i++) {
        if(p[i] != -1) {
            add_edge(&temp, p[i], i, pi[i]);
        }
    }
    for(int i=1; i<=temp.n; i++) {
        for(int j=1; j<=temp.n; j++) {
            if(temp.A[i][j] != 0) printf("%d %d %d\n", i, j, temp.A[i][j]);
        }
    }
}

Graph nhap() {
    Graph g;
    int dinh, canh;
    scanf("%d%d", &dinh, &canh);
    init_graph(&g, dinh);
    for(int i=0; i<canh; i++) {
        int u, v, e;
        scanf("%d%d%d", &u, &v, &e);
        add_edge(&g, u, v, e);
    }
    return g;
}

int main() {
    Graph g = nhap();
    prim(&g, 1);
}