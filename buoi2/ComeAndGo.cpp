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
}

int min(int a, int b) {
    if(a<b) return a;
    else return b;
}

int mark[max], on_stack[max], min_num[max], num[max], k, cnt;
Stack s;

void Tarjan(Graph *g, int x) {
    min_num[x] = num[x] = k;
    k++;
    push(&s, x);
    on_stack[x] = 1;
    mark[x] = 1;
    for(int i=1; i<=g->n; i++) {
        if(g->A[x][i] != 0) {
            if(mark[i] == 0) {
                Tarjan(g, i);
                min_num[x] = min(min_num[x], min_num[i]);
            } else if(on_stack[i] != 0) {
                min_num[x] = min(min_num[x], num[i]);
            }
        }
    }
    if(num[x] == min_num[x]) {
        cnt++;
        int temp;
        do {
            temp = pop(&s);
        } while(temp != x);
    }
}

int main() {
    Graph g;
    int dinh, canh;
    scanf("%d%d", &dinh, &canh);
    init_graph(&g, dinh);
    for(int i=1; i<=canh; i++) {
        int u, v, e;
        scanf("%d%d%d", &u, &v, &e);
        add_edge(&g, u, v);
        if(e != 1) add_edge(&g, v, u);
    }
    for(int i=1; i<=g.n; i++) {
        mark[i] = 0;
        on_stack[i] = 0;
        min_num[i] = max;
    }
    k = 1;
    cnt = 0;
    makenull_stack(&s);
    for(int i=1; i<=g.n; i++) {
        if(mark[i] == 0) Tarjan(&g, i);
    }
    if(cnt != 1) printf("NO");
    else printf("OKIE");
}