#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INFINITO 999999

typedef struct {
int cidade;
int distancia;
} Vertice;

int dijkstra(int** grafo, int numVertices, int origem, int destino, int proibido) {
int* distancias = (int*)malloc(numVertices * sizeof(int));
bool* visitado = (bool*)malloc(numVertices * sizeof(bool));
int i;

for (i = 0; i < numVertices; i++) {
    distancias[i] = INFINITO;
    visitado[i] = false;
}

distancias[origem] = 0;

for (i = 0; i < numVertices - 1; i++) {
    int menorDistancia = INFINITO;
    int verticeMenor;

    for (int v = 0; v < numVertices; v++) {
        if (!visitado[v] && distancias[v] <= menorDistancia) {
            menorDistancia = distancias[v];
            verticeMenor = v;
        }
    }

    visitado[verticeMenor] = true;

    for (int v = 0; v < numVertices; v++) {
        if (!visitado[v] && grafo[verticeMenor][v] && distancias[verticeMenor] != INFINITO &&
            distancias[verticeMenor] + grafo[verticeMenor][v] < distancias[v] && v != proibido) {
            distancias[v] = distancias[verticeMenor] + grafo[verticeMenor][v];
        }
    }
}

int menorDistancia = distancias[destino];
free(distancias);
free(visitado);

return menorDistancia;

}

int main() {
int N, M;
while (scanf("%d %d", &N, &M) != EOF) {
int** grafo = (int**)malloc(N * sizeof(int*));
int i, j;

    for (i = 0; i < N; i++) {
        grafo[i] = (int*)calloc(N, sizeof(int));
    }

    for (i = 0; i < M; i++) {
        int A, B;
        scanf("%d %d", &A, &B);
        grafo[A-1][B-1] = 1;
        grafo[B-1][A-1] = 1;
    }

    int C, R, E;
    scanf("%d %d %d", &C, &R, &E);

    int menorDistancia = dijkstra(grafo, N, C-1, R-1, E-1);
    printf("%d\n", menorDistancia);

    for (i = 0; i < N; i++) {
        free(grafo[i]);
    }
    free(grafo);
}

return 0;
}
