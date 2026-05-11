#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//DLL node structure
typedef struct Node{
    char* priority; //KEY
    char* name;
    struct Node* prev;
    struct Node* next;
} Node;

//(priority) queue structure
typedef struct Queue{
    Node* head;
} Queue;

Node* createNode(Node* head, char* priority, char* name){
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->priority, priority);
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void initQueue(Queue* pq){
    pq->head = NULL;
}

//validate command ("ADD" and "CALL")


//insert patient
void enqueue(Queue* q, char* priority, char* name){

}

int main(){
    int n;
    scanf("%d", &n);
    return 0;
}