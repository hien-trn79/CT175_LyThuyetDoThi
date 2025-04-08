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
List topo_list;

int min(int a, int b) {
    if(a < b) return a;
    else return b;
}

int maxi(int a, int b) {
    if(a>b) return a;
    else return b;
}

void rank_sort(Graph *g) {
    makenull_list(&topo_list);
    for(int i=1; i<=g->n; i++) {
        rank[i] = -1;
        for(int j=1; j<=g->n; j++) {
            if(g->A[i][j] != 0) d[j]++;
        }
    }
    List l1, l2;
    makenull_list(&l1);
    for(int i=1; i<=g->n; i++) {
        if(d[i] == 0) {
            add_list(&l1, i);
            add_edge(g, g->n+1, i);
            
        }
    }
    k = 1;
    while(l1.size > 0) {
        makenull_list(&l2);
        for(int i=0; i<l1.size; i++) {
            int t = l1.data[i];
            for(int j=1; j<=g->n; j++) {
                if(g->A[t][j] != 0) {
                    d[j]--;
                    if(d[j] == 0) add_list(&l2, j);
                }
            }
            rank[t] = k;
            add_list(&topo_list, t);
        }
        k++;
        for(int i=0; i<l2.size; i++) {
            l1.data[i] = l2.data[i];
        }
        l1.size = l2.size;
    }
}
int du[max];

Graph docFile(FILE* file) {
    Graph g;
    int dinh, m;
    fscanf(file, "%d", &dinh);
    init_graph(&g, dinh);
    for(int i=1; i<=dinh; i++) {
        fscanf(file, "%d%d", &du[i], &m);
        while(m != 0) {
            add_edge(&g, m, i);
            fscanf(file, "%d", &m);
        }
    }
    return g;
}

Graph nhap() {
    Graph g;
    int dinh, m;
    scanf("%d", &dinh);
    init_graph(&g, dinh);
    for(int i=1; i<=dinh; i++) {
        scanf("%d%d", &du[i], &m);
        while(m!=0) {
            add_edge(&g, m, i);
            scanf("%d", &m);
        }
    }
    return g;
}

int main() {
    Graph g = nhap();
    rank_sort(&g);
    for(int i=1; i<=g.n; i++) {
        for(int j=1; j<=g.n; j++) {
            if(g.A[i][j] != 0) d[j]++;
        }
    }
    // Noi cac dinh co ban bac ra bang 0 vao beta
    for(int i=1; i<=g.n; i++) {
        int cnt = 0;
        for(int j=1; j<=g.n; j++) {
            if(g.A[i][j] != 0) cnt++;
        }
        if(cnt == 0) add_edge(&g, i, g.n+2);
    }
    //Thoi gian bat dau som nhat
    int t[max];
    for(int i=1; i<=g.n; i++) {
        t[i] = -max;
    }
    t[g.n+1] = 0;
    t[topo_list.data[0]] = 0;
    for(int i=0; i<topo_list.size; i++) {
        int y = topo_list.data[i];
        for(int j=1; j<=g.n; j++) {
            if(g.A[y][j] != 0) {
                t[j] = maxi(t[j], t[y] + du[y]);
            }
        }
    }
    t[g.n+2] = t[g.n] + du[g.n];
    // Thoi gian bat dau tre nhat
    int T[max];
    for(int i=1; i<=g.n; i++) T[i] = max;
    T[g.n+2] = t[g.n+2];
    T[topo_list.data[topo_list.size-1]] = T[g.n+2] - du[topo_list.data[topo_list.size-1]];
    for(int i=topo_list.size-1; i>=0; i--) {
        int y = topo_list.data[i];
        for(int j=1; j<=g.n; j++) {
            if(g.A[j][y] != 0) {
                T[j] = min(T[j], T[y] - du[j]);
            }
        }
    }
    // In ket qua
    printf("%d\n", t[g.n+2]);
    for(int i=1; i<=g.n+2; i++) {
        printf("%d-%d\n", t[i], T[i]);
    }
}