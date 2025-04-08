#include <stdio.h>
#define max 100

typedef struct {
    int n;
    int A[max][max];
} Graph;

typedef struct {
    int top;
    int data[max];
} Stack;

void makenull_stack(Stack *s) {
    s->top = max;
}

int empty_stack(Stack s) {
    return s.top == max;
}

void push(Stack *s, int x) {
    s->top--;
    s->data[s->top] = x;
}

int pop(Stack *s) {
    int temp = s->top;
    s->top++;
    return s->data[temp];
}

void init_graph(Graph *g, int n) {
    g->n = n;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) g->A[i][j] = 0;
    }
}

void add_edge(Graph *g, int u, int v) {
    g->A[u][v] = 1;
    g->A[v][u] = 1;
}

int mark[max];
int daDuyet[max];
int k;

void dfs(Graph *g, int x) {
    Stack choXet;
    makenull_stack(&choXet);
    push(&choXet, x);
    while(!empty_stack(choXet)) {
        int u = pop(&choXet);
        if(mark[u] == 0) {
            mark[u] = 1;
            if(daDuyet[k] == -1) {
                daDuyet[k] = u;
                k++;
            }
            for(int i=1; i<=g->n; i++) {
                if(g->A[u][i] != 0) {
                    push(&choXet, i);
                }
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
        add_edge(&g, u, v);
    }
    for(int i=1; i<=g.n; i++) {
        mark[i] = 0;
        daDuyet[i-1] = -1;
    }
    k=0;
    for(int i=1; i<=g.n; i++) {
        if(mark[i] == 0) dfs(&g, i);
    }
    for(int i=0; i<k; i++) {
        printf("%d\n", daDuyet[i]);
    }
}