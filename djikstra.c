#include "vector_int.h"
#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "limits.h"

vectorInt* weights;
vectorInt* neighbours;

int* visited;
int* dist;

void init(int n, int root){
    weights = malloc(n*sizeof(vectorInt));
    neighbours = malloc(n*sizeof(vectorInt));
    dist = malloc(n*sizeof(int));

    for(int i = 0; i < n; i++){
        dist[i] = INT_MAX;
        init_vector(&weights[i]);
        init_vector(&neighbours[i]);
    }

    dist[root] = 0;
} //allocating all the memory and getting ready for war

void addEdge(int start, int end, int weight){
    push_back(&neighbours[start], end);
    push_back(&weights[start], weight);
} //using for the initialization of the graph and storing it

void cleanup(int n){
    for (int i = 0; i < n; i++){
        clear_vector(&weights[i]);
        clear_vector(&neighbours[i]);
    }
    free(weights);
    free(neighbours);
    free(dist);
    free(visited);
} //cleaning up the allocated memory

int main(){
    char* graphs[] = {"graph1.txt", "graph2.txt", "graph3.txt"};
    printf("Enter the number of the graph example of your choice: (1-3): ");
    int graphNum;
    scanf("%d", &graphNum);

    FILE* input_file;
    if(!(1 <= graphNum && graphNum <= 3)){
        printf("Enter valid number!\n");
        return 0;
    }

    input_file = fopen(graphs[graphNum-1], "r");

    if(input_file == NULL){
        printf("Check the filename!\n");
        return 0;
    }

    int n, m;
    fscanf(input_file, "%d %d", &n, &m);

    int root;
    printf("Enter the source node number (0-indexing) from (%d-%d): ", 0 , n-1);
    scanf("%d", &root);

    init(n, root);

    for(int i = 0; i < m; i++){
        int u, v, w;
        fscanf(input_file, "%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    } //input and initializing graph (in this case oriented graph (one-way edges only))

    PriorityQueue pq;
    pq_init(&pq, n);
    pq_push(&pq, 0, root);

    while(!pq_empty(&pq)){
        PQNode top = pq_top(&pq);
        pq_pop(&pq);

        int u = top.node;
        int d = top.dist;

        if(d > dist[u])
            continue; //pruning

        for(int i = 0; i < neighbours[u].size; i++){
            int v = neighbours[u].data[i];
            int w = weights[u].data[i];

            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq_push(&pq, dist[v], v);
            }
        }
    }

    pq_free(&pq);

    for(int i = 0; i < n; i++){
        printf("Vertex: %d, Distance from (%d): ", i, root);
        if(i == root){
            printf("Source node");
        }
        else if(dist[i] == INT_MAX){
            printf("Can't reach");
        }
        else {
            printf("%d", dist[i]);
        }
        printf("\n");
    }

    cleanup(n);
    fclose(input_file);
    return 0;
}