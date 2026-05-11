#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//DLL node structure
typedef struct Node{
    int x;
    char* name;
    struct Node* prev;
    struct Node* next;
} Node;

//queue structure
typedef struct Queue{
    Node* front;
    Node* rear;
} Queue;

Queue* createQueue(){
    Queue* newQ = (Queue*)malloc(sizeof(Queue));
    newQ->front = newQ->rear = NULL;
    return newQ;
}

//utility for validating name thing
int isValidName(char* name){
    int len = strlen(name);
    if (len < 1 || len > 20) return 0;

    for (int i = 0; i < len; i++){
        char c = name[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')){
            return 0;
        }
    }
    return 1;
}

//utility for checking if queue empty or na
int isEmpty(Queue* q){
    return q->front == NULL;
}

//add to the back
void enqueue(Queue* q, int x, char* name){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->x = x;
    newNode->name = strdup(name); //basically copying the string, strdup is for avoiding scope issues
    newNode->next = NULL;
    newNode->prev = q->rear;

    if (isEmpty(q)){
        q->front = q->rear = newNode;
    } else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

//remove at the front (cuz fifo lol)
void dequeue(Queue* q){
    if (isEmpty(q)){
        printf("Printer Idle\n");
        return;
    }
    printf("%d %s\n", q->front->x, q->front->name);
    Node* temp = q->front;
    q->front = q->front->next;

    //if queue becomes empty
    if (q->front == NULL){
        q->rear = NULL;
    } else{
        q->front->prev = NULL;
    }
    free(temp->name);
    free(temp);
}

void peek(Queue* q){
    if (isEmpty(q)){
        printf("Printer Idle\n");
    } else{
        printf("%d %s\n", q->front->x, q->front->name);
    }
}

int main(){
    int qCount, id;
    char name[21];
    scanf("%d", &qCount);
    Queue* q = createQueue();

    for (int i = 0; i < qCount; i++){
        int op;
        scanf("%d", &op);

        if (op == 1){
            scanf("%d %s", &id, name);
            if (isValidName(name)){
                enqueue(q, id, name);
            }
        } else if (op == 2){
            dequeue(q);
        } else if (op == 3){
            peek(q);
        }
    }
    return 0;
}