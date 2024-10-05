#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX  // Define infinity as maximum value of integer

// Function to find the vertex with minimum distance which is not yet processed
int minDistance(int dist[], int visited[], int vertices) {
    int min = INF, min_index;

    for (int v = 0; v < vertices; v++)
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

// Function to print the shortest path from source to a vertex
void printPath(int parent[], int vertex) {
    if (vertex == -1) {
        return;
    }
    printPath(parent, parent[vertex]);
    printf("%d ", vertex + 1);  // Print in 1-based index
}


void dijkstra(int graph[100][100], int vertices, int src) {
    int dist[vertices];        
    int visited[vertices];    
    int parent[vertices]; 

    for (int i = 0; i < vertices; i++) {
        parent[i] = -1;  // No parent initially
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;  // Distance from source to itself is always 0

    for (int count = 0; count < vertices - 1; count++) {
        int u = minDistance(dist, visited, vertices);
        visited[u] = 1;
        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && graph[u][v] != 0 && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the results
    printf("Source\tDestination\tCost\tPath\n");
    for (int i = 0; i < vertices; i++) {
        printf("%d\t%d\t", src + 1, i + 1);
        if (dist[i] == INF) {
            printf("INF\t-\n");
        } else {
            printf("%d\t", dist[i]);
            printPath(parent, i);
            printf("\n");
        }
    }
}

int main() {
    int vertices, src;
    int graph[100][100];  // Adjacency matrix to hold the graph

    // Read the graph from the input file "inDiAdjMat1.dat"
    FILE *file = fopen("inDiAdjMat1.dat", "r");
    if (!file) {
        printf("Unable to open file.\n");
        return -1;
    }

    // Read the number of vertices
    printf("Enter the Number of Vertices: ");
    scanf("%d", &vertices);

    // Read the adjacency matrix from the file
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }
    fclose(file);

    // Get the source vertex from the user
    printf("Enter the Source Vertex: ");
    scanf("%d", &src);
    src -= 1;  // Convert to 0-based index

    // Perform Dijkstra's algorithm
    dijkstra(graph, vertices, src);

    return 0;
}
