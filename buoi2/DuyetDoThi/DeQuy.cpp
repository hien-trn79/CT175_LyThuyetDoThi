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

void add_egde(Graph* g, int u, int v) {
    g->A[u][v] = 1;
    g->A[v][u] = 1;
}

int daDuyet[max];
int mark[max];
int k;

void dfs(Graph* g, int x) {
    if(mark[x] == 0) {
        mark[x] = 1;
        if(daDuyet[k] == -1) {
            daDuyet[k] = x;
            k++;
        }
        for(int i=1; i<=g->n; i++) {
            if(g->A[x][i] != 0) {
                dfs(g, i);
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
        int u, v;
        scanf("%d%d", &u, &v);
        add_egde(&g, u, v);
    }
    for(int i=1; i<=g.n; i++) {
        mark[i] = 0;
        daDuyet[i-1] = -1;
    }
    k = 0;
    for(int i=1; i<=g.n; i++) {
        if(mark[i] == 0) dfs(&g, i);
    }
    for(int i=0; i<k; i++) {
        printf("%d\n", daDuyet[i]);
    }
}