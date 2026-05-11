#include <stdio.h>
#include <stdlib.h>

//struct for edge of a graph
struct Edge{
    int src, dest; //src = source vertex, dest = destination vertex
};

//struct for graph
struct Graph{
    int v, e; //v = num of vertices, e = num of edges
    struct Edge* edge; //array of edges
};

//function to create graph
struct Graph* createGraph(int v, int e){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->v = v;
    graph->e = e;
    graph->edge = (struct Edge*)malloc(graph->e * sizeof(struct Edge));
    return graph;
}

//function to find the parent of a vertex
int findParent(int* parent, int vertex){
    if (parent[vertex] == -1) return vertex; //if vertex is its own parent, return vertex
    parent[vertex] = findParent(parent, parent[vertex]); //path compression (so that the finding process is faster in future. for optimization)
    return parent[vertex];
}

//function to detect a cycle
int isCycle(struct Graph* graph){
    //create a parent array to keep track of visited vertices
    int* parent = (int*)malloc(graph->v * sizeof(int));
    for (int i = 0; i < graph->v; i++) parent[i] = -1;

    //iterate through all edges of the graph
    for (int i = 0; i < graph->e; i++){
        int src = graph->edge[i].src - 1;
        int dest = graph->edge[i].dest - 1; //subtract 1 to convert to 0-based indexing

        //find the parent of src and dest
        int parentSrc = findParent(parent, src);
        int parentDest = findParent(parent, dest);

        //if both vertices have the same parent, a cycle is detected
        if (parentSrc == parentDest){
            free(parent);
            return 1; //cycle detected
        }

        //unite the two vertices by updating the parent of one vertex to the other
        parent[parentSrc] = parentDest;
    }

    free(parent);
    return 0; //no cycle detected
}

int main(){
    int p, r; //p = num of places (vertices), r = num of roads (edges)
    scanf("%d %d", &p, &r);
    struct Graph* graph = createGraph(p, r);

    //read all edges of the graph
    for (int i = 0; i < r; i++){
        scanf("%d %d", &graph->edge[i].src, &graph->edge[i].dest);
    }

    if (isCycle(graph)){
        printf("CYCLE\n");
    } else{
        printf("SAFE\n");   
    }

    free(graph->edge);
    free(graph);
    return 0;
}