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
}

int cycle;
int mark[max];
int p[max];
void dfs(Graph *g, int x) {
    if(mark[x] == 0) {
        mark[x] = 1;
        for(int i=1; i<=g->n; i++) {
            if(g->A[x][i] != 0) {
                if(mark[i] == 0) {
                    p[i] = x;
                    dfs(g, i);
                } else if(mark[i] != 0) {
                    cycle = 1;
                    return;
                }
            }
        }
    }
}

int chutrinh(Graph *g) {
    for(int i=1; i<=g->n; i++) {
        mark[i] = 0;
        p[i] = 0;
    }
    cycle = 0;
    dfs(g, 1);
    return cycle;
}

int main() {
    Graph g;
    int dinh, canh;
    scanf("%d%d", &dinh, &canh);
    init_graph(&g, dinh);
    for(int i=0; i<canh; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&g, u , v);
    }
    if(chutrinh(&g)) printf("NO");
    else printf("YES");
}