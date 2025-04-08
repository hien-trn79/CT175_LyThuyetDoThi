#include <stdio.h>
#define max 100

// Giai bai toan me cung so theo ma tran 2 chieu

typedef struct {
    int n, m;
    int A[max][max];
} Graph;

void init_graph(Graph *g, int n, int m) {
    g->n = n;
    g->m = m;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) g->A[i][j] = 0;
    }
}
int pi[max][max];

void MeCungSo(Graph *g) {
    for(int i=1; i<=g->n; i++) {
        for(int j=1; j<=g->m; j++) {
            pi[i][j] = max;
        }
    }
    pi[1][1] = g->A[1][1];
    for(int i=1; i<=g->n; i++) {
        for(int j = 1; j<=g->m; j++) {
            int di[] = {-1, 1, 0, 0};
            int dj[] = {0, 0, -1, 1};
            for(int k=0; k<4; k++) {
                int ii = i + di[k];
                int jj = j + dj[k];
                if(ii >= 1 && ii <=g->n && jj >=1 && jj <= g->m) {
                    if(pi[i][j] + g->A[ii][jj] < pi[ii][jj]) {
                        pi[ii][jj] = pi[i][j] + g->A[ii][jj];
                    }
                }
            }
        }
    }
}

int main() {
    Graph g;
    int dinh, canh;
    scanf("%d%d", &dinh,&canh);
    init_graph(&g, dinh, canh);
    for(int i=1; i<=dinh; i++) {
        for(int j=1; j<=canh; j++) scanf("%d", &g.A[i][j]);
    }
    MeCungSo(&g);
    printf("%d", pi[g.n][g.m]);
}