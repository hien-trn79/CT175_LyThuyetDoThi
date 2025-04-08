#include <stdio.h>
#define max 100

typedef struct {
    int n;
    int A[max][max];
} Graph;

void init_graph(Graph *g, int n) {
    g->n = n;
}

void add_edge(Graph *g, int u, int v) {
    g->A[u][v] = 1;
    g->A[v][u] = 1;
}

int s, t;

Graph nhap() {
    Graph g;
    int dinh;
    scanf("%d", &dinh);
    init_graph(&g, dinh);
    for(int i=1; i<=dinh; i++) {
        for(int j=1; j<=dinh; j++) {
            int temp;
            scanf("%d", &temp);
            if(temp != 0) add_edge(&g, i, j);
        }
    }
    scanf("%d%d", &s, &t);
    return g;
}

int main() {
    s = 0;
    t = 0;
    Graph g = nhap();
    int cnt = 0;
    for(int i=1; i<=g.n; i++) {
        if(g.A[s][i] != 0 && g.A[t][i] != 0) {
            printf("%d ", i);
            cnt++;
        }
    }
    if(cnt == 0) printf("KHONG CHUNG DOI THU");
}