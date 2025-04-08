#include <stdio.h>
#define max 100

typedef struct {
    int n;
    int A[max][max];
} Graph;

typedef struct {
    int size;
    int data[max];
} List;

void makenull_list(List *l) {
    l->size = 0;
}

void add_list(List *l, int x) {
    l->data[l->size] = x;
    l->size++;
}

void init_graph(Graph *g, int n) {
    g->n = n;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) g->A[i][j] = 0;
    }
}

void add_edge(Graph *g, int u, int v) {
    g->A[u][v] = 1;
}

int d[max], rank[max], k;

void rank_sort(Graph *g) {
    for(int i=1; i<=g->n; i++) {
        rank[i] = -1;
        for(int j=1; j<=g->n; j++) {
            if(g->A[i][j] != 0) d[j]++;
        }
    }
    k = 1;
    List l1, l2;
    makenull_list(&l1);
    for(int i=1; i<=g->n; i++) {
        if(d[i] == 0) add_list(&l1, i);
    }
    while(l1.size > 0) {
        makenull_list(&l2);
        for(int i=0; i<l1.size; i++) {
            int t = l1.data[i];
            rank[t] = k;
            for(int j=1; j<=g->n; j++) {
                if(g->A[t][j] != 0) {
                    d[j]--;
                    if(d[j] == 0) add_list(&l2, j);
                }
            }
        }
        k++;
        for(int i=0; i<l2.size; i++) {
            l1.data[i] = l2.data[i];
        }
        l1.size = l2.size;
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
        add_edge(&g, v, u);
    }
    rank_sort(&g);
    int sum = 0;
    for(int i=1; i<=g.n; i++) {
        sum+= rank[i];
        printf("%d\n", rank[i]);
    }
    printf("%d", sum);
}