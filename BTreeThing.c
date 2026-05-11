#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 3 //max degree

typedef struct Node{
    int numKeys; //number of keys
    int keys[M - 1]; //maximum keys
    Node* children[M]; //array of child pointers
    bool isLeaf; //true if is leaf
} Node;

Node* createNode(bool isLeaf){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL){
        return 1;
    }
    newNode->numKeys = 0;
    for (int i = 0; i < M; i++){
        newNode->children[i] = NULL;
    }
    newNode->isLeaf = isLeaf;
    return newNode;
}

//utility for the operations (insertion, deletion, searching)
void splitChild(Node* parent, int index){
    Node* child = parent->children[index]; //
    Node* newNode = createNode(child->isLeaf);

    newNode->numKeys = (M/2) - 1;

    //move keys and children to the new node
    for (int i = 0; i < M/2 - 1; i++){

    }
}

void nonFullInsert(Node* parent, int index){
    //usual bst insertion
}

void insert(){
    //usual bst insertion
}

void remove(){

}

void search(){

}

void traverse(){

}

int main(){
    return 0;
}