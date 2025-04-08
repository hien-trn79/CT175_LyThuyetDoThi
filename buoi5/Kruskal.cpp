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

Graph docFile(FILE *file) {
    Graph g;
    int dinh, canh;
    fscanf(file, "%d%d", &dinh, &canh);
    init_graph(&g, dinh);
    for(int i=0; i<canh; i++) {
        int u, v, e;
        fscanf(file, "%d%d%d", &u, &v, &e);
        add_edge(&g, u, v, e);
    }
    return g;
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

int parent[max];
void Kruskal(Graph *g) {
    Graph temp;
    int sum = 0;
    init_graph(&temp, g->n);
    for(int i=1; i<=g->n; i++) {
        parent[i] = i;
    }
    for(int i=0; i<g->m; i++) {
        for(int j=i+1; j<g->m; j++) {
            if(g->edges[i].e > g->edges[j].e) {
                Edge temp = g->edges[i];
                g->edges[i] = g->edges[j];
                g->edges[j] = temp;
            }
        }
    }
    for(int i=0; i<g->m; i++) {
        int u = g->edges[i].u;
        int v = g->edges[i].v;
        int e = g->edges[i].e;
        int root_u = parent[u];
        int root_v = parent[v];
        if(root_u != root_v) {
            add_edge(&temp, u, v, e);
            sum += e;
            for(int i=1; i<=g->n; i++) {
                if(parent[i] == root_v) {
                    parent[i] = root_u;
                }
            }
        }
    }
    printf("%d\n", sum);
    for(int i=0; i<temp.m; i++) {
        if(temp.edges[i].u > temp.edges[i].v) {
            printf("%d %d %d\n", temp.edges[i].v, temp.edges[i].u, temp.edges[i].e);
        }
        else printf("%d %d %d\n", temp.edges[i].u, temp.edges[i].v, temp.edges[i].e);
    }
}

int main() {
    // FILE *file = fopen("buoi5.txt", "r");
    // Graph g = docFile(file);
   Graph g = nhap();
    Kruskal(&g);
}