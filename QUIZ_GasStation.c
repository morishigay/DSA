#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int id;
    int fuel;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int id, int fuel){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    newNode->fuel = fuel;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

typedef struct Queue{
    Node* front;
    Node* rear;
} Queue;

Queue* initQueue(){
    Queue* newQ = (Queue*)malloc(sizeof(Queue));
    newQ->front = newQ->rear = NULL;
    return newQ;
}

void enqueue(Queue* q, int id, int fuel){
    
}

void dequeue(Queue* q, int fuel){

}

void freeQueue(Queue* q){

}

int main(){
    Queue* q = initQueue();
    return 0;
}