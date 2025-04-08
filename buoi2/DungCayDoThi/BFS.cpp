#include <stdio.h>
#define max 100

typedef struct {
    int front, rear;
    int data[max];
} Queue;

typedef struct {
    int n;
    int A[max][max];
} Graph;

void makenull_queue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int empty_queue(Queue q) {
    if(q.front == -1 && q.rear == -1) return 1;
    else return 0;
}

void push(Queue *q, int x) {
    q->rear++;
    if(empty_queue(*q)) {
        q->front++;
    }
    q->data[q->rear] = x;
}

int pop(Queue *q) {
    int temp = q->front;
    if(q->front == q->rear) {
        makenull_queue(q);
    } else {
        q->front++;
    }
    return q->data[temp];
}

void init_graph(Graph *g, int n)  {
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
int p[max];

void bfs(Graph *g, int x) {
    Queue choXet;
    makenull_queue(&choXet);
    push(&choXet, x);
    while(!empty_queue(choXet)) {
        int u = pop(&choXet);
        if(mark[u] == 0) {
            mark[u] = 1;
            for(int i=1; i<=g->n; i++) {
                if(g->A[u][i] != 0) {
                    if(mark[i] == 0) {
                        push(&choXet, i);
                        if(p[i] == 0) p[i] = u;
                    }
                }
            }
        }
    }
}

int main() {
    Graph g;
    int dinh, canh;
    scanf("%d%d",&dinh, &canh);
    init_graph(&g, dinh);
    for(int i=0; i<canh; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&g, u, v);
    }
    for(int i=1; i<=g.n; i++) {
        mark[i] = 0;
        p[i] = 0;
    }
    for(int i=1; i<=g.n; i++) {
        if(mark[i] == 0) bfs(&g, i);
    }
    for(int i=1; i<=g.n; i++) {
        printf("%d %d\n", i, p[i]);
    }
}