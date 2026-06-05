#include <stdio.h>
#include <stdlib.h>

//function to find the parent of a vertex
int findParent(int* parent, int vertex){
    if (parent[vertex] == -1) return vertex; //if vertex is their own parent, return vertex
    parent[vertex] = findParent(parent, parent[vertex]); //path compression for optimization
    return parent[vertex]; //return parent of the vertex
}

int main(){
    int p, r; //p = num of places (vertices), r = num of roads (edges)
    scanf("%d %d", &p, &r);

    //if there are no roads, it's safe
    if (r == 0){
        printf("SAFE\n");
        return 0;
    }

    //make a parrent array for union-find
    int* parent = (int*)malloc(p * sizeof(parent));
    for (int i = 0; i < p; i++){ //initialize all vertices as their own parent
        parent[i] = -1;
    }

    int cycle = 0; //flag for cycle detection
    for (int i = 0; i < r; i++){ //iterate through all roads
        int src, dest;
        scanf("%d %d", &src, &dest);
        src--; dest--;

        //find parents for src and dest
        int srcParent = findParent(parent, src);
        int destParent = findParent(parent, dest);

        //if both are the same, cycle detected
        if (srcParent == destParent){
            cycle = 1;
            break;
        }
        parent[srcParent] = destParent; //unite the two sets
    }

    //print result
    if (cycle){
        printf("CYCLE\n");
    } else{
        printf("SAFE\n");
    }
    free(parent);
}
