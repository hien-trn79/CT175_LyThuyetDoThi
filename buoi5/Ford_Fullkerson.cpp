#include <stdio.h>
#define max 100

typedef struct {
    int c[max][max];
    int f[max][max];
    int n;
} Graph;

typedef struct {
    int front, rear;
    int data[max];
} Queue;

typedef struct {
    int dir, par, sigma;
} Label;

Label labels[max];

void init_graph(Graph *g, int n) {
    g->n = n;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            g->f[i][j] = 0;
        }
    }
}

void makenull_queue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int empty_queue(Queue q) {
    if(q.front == -1 && q.rear == -1) return 1;
    else return 0;
}

void push(Queue *q, int x) {
    if(empty_queue(*q)) {
        q->front++;
    }
    q->rear++;
    q->data[q->rear] = x;
}

int pop(Queue *q) {
    int temp = q->front;
    if(q->front == q->rear) {
        makenull_queue(q);
    }
    else q->front++;
    return q->data[temp];
}

Graph docFile(FILE* file) {
    Graph g;
    int dinh, canh;
    fscanf(file, "%d%d", &dinh, &canh);
    init_graph(&g, dinh);
    for(int i=0; i<canh; i++) {
        int u, v, e;
        fscanf(file, "%d%d%d", &u, &v, &e);
        g.c[u][v] = e;
    }
    return g;
}

int min(int a, int b) {
    if(a<b) return a;
    else return b;
}

int Ford_fullkerson(Graph *g, int s, int t) {
    int sum_flow = 0;
    do {
        // xoa nhan
        for(int i=1; i<=g->n; i++) {
            labels[i].dir = 0;
        }
        //Gan nhan cho dinh phat
        labels[s].dir = 1;
        labels[s].par = s;
        labels[s].sigma = max;
        Queue q;
        makenull_queue(&q);
        push(&q, s);
        int found = 0;
        while((!empty_queue(q)) && (found == 0)) {
            int x = pop(&q);
            for(int i=1; i<=g->n; i++) {
                if(g->c[x][i] != 0 && labels[i].dir == 0 && g->f[x][i] < g->c[x][i]) {
                    labels[i].dir = 1;
                    labels[i].par = x;
                    labels[i].sigma = min(labels[x].sigma, g->c[x][i] - g->f[x][i]);
                    push(&q, i);
                }
                if(g->c[i][x] != 0 && labels[i].dir == 0 && g->f[i][x] > 0) {
                    labels[i].dir = -1;
                    labels[i].par = x;
                    labels[i].sigma = min(g->f[x][i], labels[i].sigma);
                    push(&q, i);
                }
            }
            if(labels[t].dir != 0) {
                found = 1;
                break;
            }
        }
        if(found == 1) {
            int u = t;
            sum_flow += labels[t].sigma;
            while(u != s) {
                int x = labels[u].par;
                int sigma = labels[t].sigma;
                if(labels[u].dir > 0) {
                    g->f[x][u] += sigma;
                } else {
                    g->f[x][u] -= sigma;
                }
                u = x;
            }
        } else {
            break;
        }
    } while(1);
    return sum_flow;
}

Graph nhap() {
    Graph g;
    int dinh, canh;
    scanf("%d%d", &dinh, &canh);
    init_graph(&g, dinh);
    for(int i=0; i<canh; i++) {
        int u, v, e;
        scanf("%d%d%d", &u, &v, &e);
        g.c[u][v] = e;
    }
    return g;
}

int main() {
    Graph g = nhap();
    printf("Max flow: %d\n", Ford_fullkerson(&g, 1, g.n));
    printf("X0: ");
    for(int i=1; i<=g.n; i++) {
        if(labels[i].dir != 0) printf("%d ", i);
    }
    printf("\nY0: ");
    for(int i=1; i<=g.n; i++) {
        if(labels[i].dir == 0) printf("%d ", i);
    }
}